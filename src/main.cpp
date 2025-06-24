#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include "knn.h"

using namespace std;

void speak(const std::string& text) {
    std::string command = "cmd /c \"C:/Users/unaiz/OneDrive/Documents/KNNNNN/src/espeak-ng.exe \"" + text + "\"\"";
    system(command.c_str());
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    string imageFile = "C:/Users/unaiz/OneDrive/Desktop/CustomDigitDataset/build/Debug/data/images.bin"; 
    string labelFile = "C:/Users/unaiz/OneDrive/Desktop/CustomDigitDataset/build/Debug/data/labels.bin";
    int numImages = 0;
    int numLabels = 0;
    int k = 3;

    // Load custom dataset
    vector<Image> trainingImages = readCustomImages(imageFile, numImages);
    vector<int> trainingLabels = readCustomLabels(labelFile, numLabels);

    cout << "Number of images loaded: " << numImages << endl;
    cout << "Number of labels loaded: " << numLabels << endl;

    if (numImages != numLabels) {
        cerr << "Error: The number of images and labels do not match!" << endl;
        return 1;
    }

    // Assign labels to images
    for (int i = 0; i < numImages; ++i) {
        trainingImages[i].label = trainingLabels[i];
    }

    cout << "Custom dataset loaded: " << numImages << " images" << endl;
    speak("Custom dataset loaded");

    int score = 0;
    string userInput;
    int testCount = 0;
    int totalTests = 5;
    cout << "............WELCOME TO THE KIDS LEARNING TOOL............" << endl;
    speak("WELCOME TO THE KIDS LEARNING TOOL");

    while (true) {
        if (testCount >= totalTests) {
            cout << "Would you like to take another test session? (yes/no): ";
            speak("Would you like to take another test session?");
            cin >> userInput;
            if (userInput == "no") {
                cout << "Goodbye!" << endl;
                speak("Goodbye!");
                break;
            }
            score = 0;
            testCount = 0;
        }

        int targetDigit = rand() % 10;
        cout << "\nPlease draw the digit: " << targetDigit << endl;
        speak("Please draw the digit " + std::to_string(targetDigit));

        sf::RenderWindow window(sf::VideoMode(280, 280), "Draw a Digit");
        sf::RectangleShape pixel(sf::Vector2f(10, 10));
        vector<unsigned char> customImageData(28 * 28, 0);
        bool isDrawing = false;

        while (window.isOpen()) {
            window.setTitle("Draw the digit: " + to_string(targetDigit) + " | Press 'C' to clear, Enter to submit");

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        window.close();  // Close window when Enter is pressed
                    }
                    else if (event.key.code == sf::Keyboard::C) {
                        // Clear the canvas
                        fill(customImageData.begin(), customImageData.end(), 0);
                        cout << "Canvas cleared!" << endl;
                    }
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        isDrawing = true;
                    }
                }
                else if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        isDrawing = false;
                    }
                }
            }

            if (isDrawing) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                int x = position.x / 10;
                int y = position.y / 10;
                if (x >= 0 && x < 28 && y >= 0 && y < 28) {
                    // Draw a thicker line (3x3 pixels)
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            int newX = x + dx;
                            int newY = y + dy;
                            if (newX >= 0 && newX < 28 && newY >= 0 && newY < 28) {
                                customImageData[newY * 28 + newX] = 255;
                            }
                        }
                    }
                }
            }

            window.clear();
            for (int i = 0; i < 28; ++i) {
                for (int j = 0; j < 28; ++j) {
                    pixel.setPosition(j * 10.0f, i * 10.0f);
                    pixel.setFillColor(customImageData[i * 28 + j] == 255 ? sf::Color::White : sf::Color::Black);
                    window.draw(pixel);
                }
            }
            window.display();
        }

        bool hasDrawing = any_of(customImageData.begin(), customImageData.end(),
                               [](unsigned char pixel) { return pixel > 0; });
        if (!hasDrawing) {
            cout << "No digit was drawn. Please try again!" << endl;
            speak("No digit was drawn. Please try again!");
            continue;
        }

        Image customImage = {customImageData};
        int predictedLabel = knn(trainingImages, customImage, k);
        cout << "You drew the digit: " << predictedLabel << endl;
        speak("You drew the digit: " + std::to_string(predictedLabel));

        if (predictedLabel == targetDigit) {
            cout << "Correct! You get a point!" << endl;
            speak("Correct!");
            score++;
        } else {
            cout << "Incorrect! No points." << endl;
            speak("Incorrect!");
        }

        cout << "Your score: " << score << " / " << totalTests << endl;
        speak("Your score: " + std::to_string(score));
        if (score > 3) {
            cout << "Great job! You scored more than 3!" << endl;
            speak("Great job! You scored more than 3!");
        }

        testCount++;
    }

    return 0;
}

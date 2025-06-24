#include "knn.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

// Byte swap function to handle endian differences
uint32_t swap32(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}

// Function to calculate Euclidean distance between two images
// Normalize pixel values in calculateDistance
double calculateDistance(const Image& a, const Image& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.pixels.size(); ++i) {
        double diff = (a.pixels[i] / 255.0) - (b.pixels[i] / 255.0);
        sum += diff * diff;  // Squared difference
    }
    return sqrt(sum);  // Take square root for Euclidean distance
}

// Use partial sort in knn to find k nearest neighbors efficiently
int knn(const vector<Image>& trainingData, const Image& testImage, int k) {
    vector<pair<double, int>> distances;

    for (const auto& trainImage : trainingData) {
        double dist = calculateDistance(trainImage, testImage);
        distances.emplace_back(dist, trainImage.label);
    }

    std::partial_sort(distances.begin(), distances.begin() + k, distances.end());

    vector<int> labelCount(10, 0);
    for (int i = 0; i < k; ++i) {
        labelCount[distances[i].second]++;
    }

    return static_cast<int>(max_element(labelCount.begin(), labelCount.end()) - labelCount.begin());
}


// Function to read MNIST images
vector<Image> readMNISTImages(const string& fileName, int& numImages, int maxImages) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return {};
    }

    int magicNumber = 0, rows = 0, cols = 0;
    file.read(reinterpret_cast<char*>(&magicNumber), 4);
    file.read(reinterpret_cast<char*>(&numImages), 4);
    file.read(reinterpret_cast<char*>(&rows), 4);
    file.read(reinterpret_cast<char*>(&cols), 4);

    numImages = swap32(numImages);
    rows = swap32(rows);
    cols = swap32(cols);

    numImages = min(numImages, maxImages);  // Limit the number of images to maxImages
    vector<Image> images(numImages);
    int imageSize = rows * cols;

    for (int i = 0; i < numImages; ++i) {
        images[i].pixels.resize(static_cast<int>(imageSize));
        file.read(reinterpret_cast<char*>(images[i].pixels.data()), imageSize);
    }

    return images;
}

// Function to read MNIST labels
vector<int> readMNISTLabels(const string& fileName, int& numLabels, int maxLabels) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return {};
    }

    int magicNumber = 0;
    file.read(reinterpret_cast<char*>(&magicNumber), 4);
    file.read(reinterpret_cast<char*>(&numLabels), 4);

    numLabels = swap32(numLabels);
    numLabels = min(numLabels, maxLabels);  // Limit the number of labels to maxLabels

    vector<int> labels(numLabels);
    for (int i = 0; i < numLabels; ++i) {
        unsigned char label;
        file.read(reinterpret_cast<char*>(&label), 1);
        labels[i] = label;
    }

    return labels;
}

// Function to sample dataset randomly (optional for testing)
void sampleDataset(vector<Image>& images, vector<int>& labels, int sampleSize) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, images.size() - 1);

    vector<Image> sampledImages;
    vector<int> sampledLabels;
    for (int i = 0; i < sampleSize; ++i) {
        int idx = dis(gen);
        sampledImages.push_back(images[idx]);
        sampledLabels.push_back(labels[idx]);
    }

    images = sampledImages;
    labels = sampledLabels;
}

// Function to read images from binary file
vector<Image> readCustomImages(const string& fileName, int& numImages) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return {};
    }

    // Read the entire file content into a vector
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    numImages = static_cast<int>(fileSize / (28 * 28));  // Each image is 28x28 pixels
    vector<Image> images(numImages);

    for (int i = 0; i < numImages; ++i) {
        images[i].pixels.resize(28 * 28);
        file.read(reinterpret_cast<char*>(images[i].pixels.data()), 28 * 28);
    }

    return images;
}

// Function to read labels from binary file
vector<int> readCustomLabels(const string& fileName, int& numLabels) {
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return {};
    }

    // Read the entire file content into a vector
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    numLabels = static_cast<int>(fileSize);  // Each label is one byte
    vector<int> labels(numLabels);

    for (int i = 0; i < numLabels; ++i) {
        unsigned char label;
        file.read(reinterpret_cast<char*>(&label), 1);
        labels[i] = label;
    }

    return labels;
}

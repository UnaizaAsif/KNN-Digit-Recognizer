#ifndef KNN_H
#define KNN_H

#include <vector>
#include <string>

struct Image {
    std::vector<unsigned char> pixels;
    int label;
};

// Function declarations
uint32_t swap32(uint32_t value);
double calculateDistance(const Image& a, const Image& b);
int knn(const std::vector<Image>& trainingData, const Image& testImage, int k);
std::vector<Image> readMNISTImages(const std::string& fileName, int& numImages, int maxImages);
std::vector<int> readMNISTLabels(const std::string& fileName, int& numLabels, int maxLabels);
void sampleDataset(std::vector<Image>& images, std::vector<int>& labels, int sampleSize);
std::vector<Image> readCustomImages(const std::string& fileName, int& numImages);
std::vector<int> readCustomLabels(const std::string& fileName, int& numLabels);

#endif // KNN_H

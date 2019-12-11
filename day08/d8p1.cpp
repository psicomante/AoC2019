#include <iostream>
#include <fstream>
#include <cmath>
#include "../InputIO.h"
#include <vector>
#include <array>

using namespace std;

int countLayerStats(const string& imgPixels, int w, int h) {
    int imgSize = w*h;
    if ((int)imgPixels.size() % imgSize)
        throw runtime_error("bad-sized input");

    int checksum = 0x7ffffff;
    unsigned int fewestZeros = UINT_MAX;

    for (auto it = imgPixels.begin(); it != imgPixels.end(); it += imgSize)
    {
        int num0 = count(it, it + imgSize, '0');
        if (num0 < fewestZeros)
        {
            int num1 = count(it, it + imgSize, '1');
            int num2 = count(it, it + imgSize, '2');
            checksum = num1 * num2;
            fewestZeros = num0;
        }
    }

    return checksum;
}

string decodeImage(const string& imgPixels, int w, int h) {
    int imgSize = w*h;

    if ((int)imgPixels.size() % w*h)
        throw runtime_error("bad-sized input");

    int nl = (int)imgPixels.size() / imgSize;

    string decodedImage;

    for (int iit = 0; iit < imgSize; iit++){
        int lit = 0;

        while(imgPixels[lit*imgSize + iit] == '2' && lit < nl) {
            lit++;
        }

        if (lit*imgSize + iit >= imgPixels.size()) {
            throw runtime_error("bad iterator");
        }

        decodedImage.push_back(imgPixels[lit*imgSize + iit]);
    }

    return decodedImage;
}

void printImage(const string& decodedImage, int w, int h) {
    for (int i = 0; i < decodedImage.size(); i++) {
        if (i % w*h == 0) {
            cout << endl;
        }

        cout << (decodedImage.at(i) == '0' ? ' ' : '#');
    }
}

int main() {
    std::cout << "--- Day 8: Space Image Format ---" << endl;

    vector<string> lines = readInput(8,1);
    string imgPixels = lines.at(0);

    assert(countLayerStats("123456789012", 3, 2) == 1);
    assert(countLayerStats("121001011223", 3, 2) == 4);

    int stats = countLayerStats(imgPixels, 25, 6);

    cout << "part1: " << stats << endl;

    assert(decodeImage("0222112222120000", 2, 2) == "0110");

    string decodedImage = decodeImage(imgPixels, 25, 6);
    cout << "part2: " << decodedImage << endl;

    printImage(decodedImage, 25, 6);

    return 0;
}

#ifndef ADVENTOFCODE_INPUTIO_H
#define ADVENTOFCODE_INPUTIO_H

#include <vector>

using namespace std;

vector<string> readInput(int day, int part) {
    std::ifstream infile("d" + to_string(day) + "p" + to_string(part) + ".txt");

    if (!infile.is_open()) throw runtime_error("Error opening the file");

    std::string line;
    std::vector<string> lines;

    while(infile >> line) {
        lines.push_back(line);
    }

    if(infile.bad()) throw runtime_error("Error reading the file");

    return lines;
}

vector<int> splitToInt(string line, char separator) {
    vector<int> list = {};
    string buff;

    for (char chr : line) {
        if (chr != separator) {
            buff += chr;
        }
        else {
            list.push_back(stoi(buff));
            buff = "";
        }
    }

    if (!buff.empty()) {
        list.push_back(stoi(buff));
    }

    return list;
}

#endif //ADVENTOFCODE_INPUTIO_H

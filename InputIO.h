#ifndef ADVENTOFCODE_INPUTIO_H
#define ADVENTOFCODE_INPUTIO_H

#include <vector>

using namespace std;

vector<string> readInput(int day, int part) {
    std::ifstream infile("d" + to_string(day) + "p" + to_string(part) + ".txt");

    std::string line;
    std::vector<string> lines;
    while(infile >> line) {
        lines.push_back(line);
    }

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

#include <iostream>
#include <fstream>
#include <cmath>
#include "../InputIO.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool hasTwoAdjacent(string s) {
    for(int i = 1; i<s.size(); i++) {
        if (s.at(i) == s.at(i-1)) {
            return true;
        }
    }

    return false;
}

bool hasExactlyTwoAdj(string s) {
    int a[10] = {0};
    int counter = 0;
    for (int i = 1; i<s.size(); i++) {
        if (s.at(i) == s.at(i-1)) {
            char c = s.at(i);
            int d = atoi(&c);
            a[d] += 1;
        }
    }

    bool hasTwoAdj = false;
    for (int c : a) {
        if (c == 1) {
            return true;
        }
    }

    return false;
}

bool isDigitMonotone(string s) {
    for (int i = 1; i<s.size(); i++) {
        if (s.at(i) < s.at(i-1)) {
            return false;
        }
    }

    return true;
}

int main() {
    std::cout << "--- Day 4: Secure Container ---" << endl;

    string input = "108457-562041";
    vector<int> range = splitToInt(input, '-');

    assert(hasTwoAdjacent("111111") && isDigitMonotone("111111"));
    assert(!(hasTwoAdjacent("223450") && isDigitMonotone("223450")));
    assert(!(hasTwoAdjacent("123789") && isDigitMonotone("123789")));

    assert((hasExactlyTwoAdj("112233") && isDigitMonotone("112233")));
    assert(!(hasExactlyTwoAdj("123444") && isDigitMonotone("123444")));
    assert((hasExactlyTwoAdj("111122") && isDigitMonotone("111122")));

    int l = range.at(0);
    int u = range.at(1);

    int matchingStep1 = 0;
    int matchingStep2 = 0;

    for (int i = l; i < u; i++) {
        string s = to_string(i);
        bool adj = hasTwoAdjacent(s);
        bool twoAdj = hasExactlyTwoAdj(s);
        bool monotone = isDigitMonotone(s);

        if (adj && monotone)
            matchingStep1++;

        if (twoAdj && monotone)
            matchingStep2++;
    }

    cout << "part1: " << matchingStep1 << endl;
    cout << "part2: " << matchingStep2 << endl;
}

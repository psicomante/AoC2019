#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "../InputIO.h"
#include "program.h"

int main() {
    std::cout << "Day 2: 1202 Program Alarm // Part 1" << endl;

    assert(program(splitToInt("1,0,0,0,99", ',')) == splitToInt("2,0,0,0,99", ','));
    assert(program(splitToInt("2,3,0,3,99", ',')) == splitToInt("2,3,0,6,99", ','));
    assert(program(splitToInt("2,4,4,5,99,0", ',')) == splitToInt("2,4,4,5,99,9801", ','));
    assert(program(splitToInt("1,1,1,4,99,5,6,0,99", ',')) == splitToInt("30,1,1,4,2,5,6,0,99", ','));

    vector<string> lines = readInput(2,1);
    vector<int> opcodes = splitToInt(lines[0], ',');

    std::cout << program_noun_verb(opcodes, 12, 2) << std::endl;

    return 0;
}

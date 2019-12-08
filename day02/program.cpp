#include <vector>

std::vector<int> program(std::vector<int> opcodes) {
    bool halt = false;
    int p = 0;
    int result = 0;
    int pos1,pos2,pos3;


    while (!halt) {
        if (opcodes[p] == 1) {
            pos1 = opcodes[p+1];
            pos2 = opcodes[p+2];
            pos3 = opcodes[p+3];
            result = opcodes[pos1] + opcodes[pos2];
            opcodes[pos3] = result;

            p = p+4;
        }

        if (opcodes[p] == 2) {
            pos1 = opcodes[p+1];
            pos2 = opcodes[p+2];
            pos3 = opcodes[p+3];
            result = opcodes[pos1] * opcodes[pos2];
            opcodes[pos3] = result;

            p = p+4;
        }

        if (opcodes[p] == 99 || p > opcodes.size() - 1) {
            halt = true;
        }
    }

    return opcodes;
}

int program_noun_verb(std::vector<int> opcodes, int noun, int verb) {
    opcodes[1] = noun;
    opcodes[2] = verb;

    std::vector<int> r = program(opcodes);
    return r[0];
}
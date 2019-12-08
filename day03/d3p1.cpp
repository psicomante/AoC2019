#include <iostream>
#include <fstream>
#include <cmath>
#include "../InputIO.h"

using namespace std;

enum dir
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

struct resultIntersection {
    int distance;
    int steps;
};

class vec2 {
public:
    int x = {0};
    int y = {0};
    int steps = {0};

    vec2() : x{0}, y{0} {}

    vec2(int x, int y) : x{x}, y{y} {}

    vec2 add(int c1, int c2) {
        this->x += c1;
        this->y += c2;
        this->steps += (abs(c1) + abs(c2));
        return *this;
    }

    vec2 add(vec2 b) {
        this->x += b.x;
        this->y += b.y;
        return *this;
    }

    static vec2* intersectLine(vec2 l1a, vec2 l1b, vec2 l2a, vec2 l2b) {
        int x1 = l1a.x;
        int y1 = l1a.y;
        int x2 = l1b.x;
        int y2 = l1b.y;

        int x3 = l2a.x;
        int y3 = l2a.y;
        int x4 = l2b.x;
        int y4 = l2b.y;

        // denominator // check div/0
        int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);

        if (den != 0) {
            // intersection point (x,y)
            int x = ((x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4)) / den;
            int y = ((x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4)) / den;

            bool partOfLine1 = x >= min(x1, x2) && x <= max(x1, x2) && y >= min(y1, y2) && y <= max(y1, y2);
            bool partOfLine2 = x >= min(x3, x4) && x <= max(x3, x4) && y >= min(y3, y4) && y <= max(y3, y4);

            if (!partOfLine1 || !partOfLine2) {
                return nullptr;
            }

            return new vec2(x, y);
        }

        return nullptr;
    }

    static vec2* intersectRay(vec2 l1a, vec2 l1b, vec2 l2a, vec2 l2b) {
        int x1 = l1a.x;
        int y1 = l1a.y;

        int x2 = l1b.x;
        int y2 = l1b.y;

        int x3 = l2a.x;
        int y3 = l2a.y;

        int x4 = l2b.x;
        int y4 = l2b.y;

        // denominator of parameters t and u calculation
        int param_den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        if (param_den == 0)
            return nullptr;

        float t = float((x1-x3)*(y3-y4) - (y1-y3)*(x3-x4)) / float(param_den);
        float u = float((x1-x2)*(y1-y3) - (y1-y2)*(x1-x3)) / float(param_den);

        if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) {
            return new vec2(x1 + int(round(t))*(x2 - x1), y1 + int(round(t))*(y2-y1));
        }

        return nullptr;
    }

    static int dist(vec2 a, vec2 b) {
        return abs(a.x-b.x) + abs(a.y-b.y);
    }
};

class instruct {
public:
    dir direction;
    long amount;

    instruct(char dir, long amount) {
        if (dir == 'R') {
            this->direction = dir::RIGHT;
        }
        else if (dir == 'L') {
            this->direction = dir::LEFT;
        }
        else if (dir == 'U') {
            this->direction = dir::UP;
        }
        else if (dir == 'D') {
            this->direction = dir::DOWN;
        }
        this->amount = amount;
    }
};

vector<vec2> createCoordList(const vector<instruct>& wire);

vector<instruct> parseInput(const string& line) {
    vector<instruct> instructions = {};
    char letterBuffer = '0';
    string numberBuffer;

    for (char chr : line) {
        if (chr != ',') {
            if (chr == 'R' || chr == 'L' || chr == 'U' || chr == 'D') {
                letterBuffer = chr;
            }
            else {
                numberBuffer += chr;
            }
        }
        else {
            auto* newInstruction = new instruct(letterBuffer, stoi(numberBuffer));
            instructions.push_back(*newInstruction);
            numberBuffer = "";
            letterBuffer = '0';
        }
    }

    if (!numberBuffer.empty()) {
        auto* newInstruction = new instruct(letterBuffer, stoi(numberBuffer));
        instructions.push_back(*newInstruction);
    }

    return instructions;
}

resultIntersection nearestIntersection(vector<vec2> wirea, vector<vec2> wireb) {
    int nearestDistance = INT_MAX;
    int lessSteps = INT_MAX;

    for (int i=0; i<wirea.size() - 1; i++) {
        for (int j=0; j<wireb.size() - 1; j++) {
            vec2* intersec = vec2::intersectLine(wirea[i], wirea[i+1], wireb[j], wireb[j+1]);
            if (intersec != nullptr) {
                int dist = abs(intersec->x) + abs(intersec->y);

                int baseSteps = wirea[i].steps + wireb[j].steps;
                baseSteps += vec2::dist(wirea[i], *intersec);
                baseSteps += vec2::dist(wireb[j], *intersec);

                if (dist < nearestDistance && dist != 0) {
                    nearestDistance = dist;
                }

                if (baseSteps < lessSteps) {
                    lessSteps = baseSteps;
                }
            }
        }
    }

    resultIntersection r{};
    r.distance = nearestDistance;
    r.steps = lessSteps;

    return r;
}

vector<vec2> createCoordList(const vector<instruct>& wire) {
    vec2 pos(0,0);
    vector<vec2> coordList;

    for(instruct i : wire) {
        if (i.direction == dir::UP) {
            pos.add(0, i.amount);
        } else if (i.direction == dir::DOWN) {
            pos.add(0, -i.amount);
        } else if (i.direction == dir::LEFT) {
            pos.add(-i.amount, 0);
        } else if (i.direction == dir::RIGHT) {
            pos.add(i.amount, 0);
        }
        coordList.emplace_back(pos);
    }

    return coordList;
}

int main() {
    std::cout << "--- Day 3: Crossed Wires ---" << endl;

    vector<string> content = readInput(3,1);
    // l is not modified, make it a reference
    for (auto& l : content) {
        cout << l << endl;
    }

    vector<instruct> wireOne = parseInput(content.at(0));
    vector<instruct> wireTwo = parseInput(content.at(1));

    vector<vec2> wireOneCoords = createCoordList(wireOne);
    vector<vec2> wireTwoCoords = createCoordList(wireTwo);

    resultIntersection r = nearestIntersection(wireOneCoords, wireTwoCoords);

    cout << r.distance << " " << r.steps;
    return 0;
}


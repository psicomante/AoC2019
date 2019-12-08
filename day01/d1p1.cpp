#include <iostream>
#include <fstream>
#include <cmath>

int mass_fuel(int m) {
    return floor(m/3.0) - 2;
}

int main() {
    std::ifstream infile("d1p1.txt");
    std::cout << "Advent Of Code: day1";

    assert(mass_fuel(12) == 2);
    assert(mass_fuel(14) == 2);
    assert(mass_fuel(1969) == 654);
    assert(mass_fuel(100756) == 33583);

    long m;
    long accum = 0;
    while(infile >> m) {
        accum += mass_fuel(m);
    }

    std::cout << std::endl << "Total Fuel: " << accum << std::endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <cmath>

int mass_fuel(int m) {
    return floor(m/3.0) - 2;
}

int module_fuel(int m) {
    int tot = 0;
    while (m > 0) {
        m = mass_fuel(m);
        tot += m;
    }

    tot -= m;
    return tot;
}

int main() {
    std::ifstream infile("d1p1.txt");
    std::cout << "Advent Of Code: day1";

    assert(module_fuel(14) == 2);
    assert(module_fuel(1969) == 966);
    assert(module_fuel(100756) == 50346);

    long m;
    long accum = 0;
    while(infile >> m) {
        accum += module_fuel(m);
    }

    std::cout << std::endl << "Total Fuel: " << accum << std::endl;
    return 0;
}

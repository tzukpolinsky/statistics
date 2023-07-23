//
// Created by tzuk on 7/6/23.
//
#include <iostream>
#include "Ttests.h"
#include "fileReader.h"


int main(int argc, char **argv) {
    std::string file = argv[1];
    //auto data = readMicrosoftStocksByYears(file, 1);
    auto data = readDataScientistsSalaryByYears(file, 6);
    double mean = 0;
    for (auto &[year, values]: data) {
        std::vector<std::vector<double>> d{values};
        Ttests test(d, 0,0.95, false, false,{mean});
        std::cout << "ztest for year " << year << " " << (test.run() ? "true":"false") << " with mean " << mean << " and var " << var
                  << std::endl;

    }
}
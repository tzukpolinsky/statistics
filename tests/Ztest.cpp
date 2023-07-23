//
// Created by tzuk on 6/28/23.
//
#include <iostream>
#include "Ztests.h"
#include "fileReader.h"


int main(int argc, char **argv) {
    std::string file = argv[1];
    //auto data = readMicrosoftStocksByYears(file, 1);
    auto data = readDataScientistsSalaryByYears(file, 6);
    double mean = 0;
    double var = 1;
    for (auto &[year, values]: data) {
        Ztests test(values, mean, var, 0.95, 0);
        std::cout << "ztest for year " << year << " " << (test.run() ? "true":"false") << " with mean " << mean << " and var " << var
                  << std::endl;

    }
}
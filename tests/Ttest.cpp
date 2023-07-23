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
//    for (auto &[year, values]: data) {
//        std::vector<std::vector<double>> d{values};
//        Ttests test(d, 0, 0.95, false, false, {mean});
//        test.run();
//        std::cout << "ztest for year " << year << " " << (test.getResults().front() ? "true" : "false") << " with mean "
//                  << mean << " and power " << test.getTestsPowers().front() << " and significance "
//                  << test.getTestsSignificances().front() << std::endl;
//
//    }
    std::vector<std::vector<double>> d;

    for (auto &[year, values]: data) {
        d.emplace_back(values);
    }
    Ttests test(d, 0, 0.95, false, true);
    test.run();
    auto results = test.getResults();
    auto testsPowers = test.getTestsPowers();
    auto testSignificance = test.getTestsSignificances();
    for (int i = 0; i < d.size(); ++i) {
        for (int j = i + 1; j < data.size(); ++j) {
            std::cout << "test for year " << i << " with year " << j << std::endl;
            std::cout << "test result " << results[j - 1] << std::endl;
            std::cout << "test significance " << testSignificance[j - 1] << std::endl;
            std::cout << "test powers " << testsPowers[j - 1] << std::endl;

        }
    }

}
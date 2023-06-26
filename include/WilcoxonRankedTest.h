//
// Created by tzuk on 6/22/23.
//

#ifndef STATISTICS_WILCOXONRANKEDTEST_H
#define STATISTICS_WILCOXONRANKEDTEST_H

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <cmath>
#include "Tables.h"
#include <iostream>

class WilcoxonRankedTest {
public:
    WilcoxonRankedTest(std::pair<std::vector<double>, std::vector<double>> &data, double confidenceLevel,
                       bool isTwoSided);

    WilcoxonRankedTest(std::vector<std::pair<double, double>> &data, double confidenceLevel, bool isTwoSided);

    double getCriticalValue();

    double getCriticalZ() const {

        if (isTwoSided) {
            return zScoreTable.lower_bound(1 - (1 - confidenceLevel) / 2)->second;
        }
        return zScoreTable.lower_bound(confidenceLevel)->second;
    }

private:
    void rank();

    std::pair<double, double> rankUnPaired();

    std::pair<double, double> createRank(int i, int amountSame, std::vector<std::pair<bool, double>> &values);

    std::pair<double, double> rankPaired();

    int size;
    int size1;
    int size2;
    bool isTwoSided;
    bool testResult;
    double confidenceLevel;
    std::pair<std::vector<double>, std::vector<double>> dataUnpaired;
    std::vector<std::pair<double, double>> dataPaired;
    std::vector<double> ranks;
    static std::map<double, double> zScoreTable;
};


#endif //STATISTICS_WILCOXONRANKEDTEST_H

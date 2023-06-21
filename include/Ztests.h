//
// Created by tzuk on 6/18/23.
//

#ifndef STATISTICS_ZTESTS_H
#define STATISTICS_ZTESTS_H

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include "Tables.h"

class Ztests {
public:
    Ztests(std::vector<double> &data, double populationMean, double populationVariance, double confidenceLevel,
           int testType);

    bool run();

    double getDataMean() const {
        return dataMean;
    }

    // Getter for statisticsZ
    double getStatisticsZ() const {
        return statisticsZ;
    }

    double getCriticalZ() const {

        if (testType == 0) {
            return zScoreTable.lower_bound(1 - (1 - confidenceLevel) / 2)->second;
        }
        return zScoreTable.lower_bound(confidenceLevel)->second;
    }

private:
    void calculateStatisticZ();

    void mean();

    static std::map<double, double> zScoreTable;
    const std::unordered_map<int, std::string> checkDirection{{-1, "left"},
                                                              {0,  "two-sides"},
                                                              {1,  "right"}};
    std::vector<double> data;
    int testType;
    bool result;
    double populationMean;
    double populationVariance;
    double confidenceLevel;
    double size;
    double dataMean;
    double statisticsZ;
};


#endif //STATISTICS_ZTESTS_H

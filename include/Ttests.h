//
// Created by tzuk on 6/18/23.
//

#ifndef STATISTICS_TTESTS_H
#define STATISTICS_TTESTS_H

#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include "Tables.h"
#include <iostream>

class Ttests {
public:
    Ttests(std::vector<std::vector<double>> &data, int testType, double confidenceLevel, bool isPaired,
           bool differentVariances,
           std::vector<double> populationMean = {std::numeric_limits<double>::max()});

    double getCriticalT(int degreesOfFreedom) const {
        if (testType == 0) {
            return tTableScore.second.lower_bound(confidenceLevel)->second.lower_bound(degreesOfFreedom)->second;
        }
        return tTableScore.second.lower_bound(confidenceLevel)->second.lower_bound(degreesOfFreedom)->second;
    }

private:
    void mean();

    void variance();

    void calculateStatisticsT();

    void calculateStatisticsTTestWithKnownPopulationMean();

    void calculateStatisticsTestsPowers(std::vector<double> &testResults);

    void calculateStatisticsTestsSignificance(std::vector<double> &testResults);

    void calculateStatisticsPairedTTests();

    void calculateStatisticsNonPairedTTests();

    void calculateStatisticsPairedTTest(std::vector<double> &data1, std::vector<double> &data2,
                                        double populationDifferenceMean);

    void calculateStatisticsNonPairedTTest(int i, int j);

    std::vector<std::vector<double>> data;
    std::pair<std::map<double, std::map<int, double>>, std::map<double, std::map<int, double>>> tTableScore;
    std::vector<double> means;
    std::vector<double> variances;
    int testType;
    std::vector<double> statisticsTs;
    std::vector<double> rawMeanDimValues;
    std::vector<double> rawMeanDiffDimValues;
    std::vector<double> testsPowers;
    std::vector<double> testsSignificance;
    std::vector<bool> results;
    std::vector<double> populationMean;
    double confidenceLevel;
    bool singleTtestCantBePreformed;
    bool pairedTtestCantBePreformed;
    bool isPaired;
    bool differentVariances;

    void calculateStatisticsNonPairedTTestWithDifferentVariances(int i, int j);

    void calculateStatisticsNonPairedTTestsWithDifferentVariance();
};


#endif //STATISTICS_TTESTS_H

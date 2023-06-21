//
// Created by tzuk on 6/18/23.
//

#ifndef STATISTICS_CONFIDENCEINTERVAL_H
#define STATISTICS_CONFIDENCEINTERVAL_H

#include <vector>
#include <map>
#include <cmath>
#include "Tables.h"

class confidenceInterval {
public:
    confidenceInterval(std::vector<double> &data, double confidenceLevel, double populationVariance);

    std::pair<double, double> run();

    std::pair<double, double> getInterval() { return interval; }

private:
    std::pair<double, double> calculateInterval();

    void mean();

    static std::map<double, double> zScoreTable;
    std::vector<double> data;
    double dataMean;
    double populationVariance;
    std::pair<double, double> interval;
    double criticalZ;
    double confidenceLevel;
    double intervalLength;
};

class confidenceIntervalT {
public:
    confidenceIntervalT(std::vector<double> &data, double confidenceLevel);

    std::pair<double, double> run();

    std::pair<double, double> getInterval() { return interval; }

private:
    std::pair<double, double> calculateInterval();

    void mean();

    void variance();


    std::pair<std::map<double, std::map<int, double>>, std::map<double, std::map<int, double>>> tTableScore;
    std::vector<double> data;
    double dataMean;
    double dataVariance;
    std::pair<double, double> interval;
    double criticalT;
    double confidenceLevel;
    double intervalLength;
};

#endif //STATISTICS_CONFIDENCEINTERVAL_H

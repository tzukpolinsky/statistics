//
// Created by tzuk on 6/18/23.
//

#include "confidenceInterval.h"

confidenceInterval::confidenceInterval(std::vector<double> &data, double confidenceLevel, double populationVariance)
        : data(data), confidenceLevel(confidenceLevel),
          populationVariance(populationVariance) {
    zScoreTable = createZTable();
    criticalZ = zScoreTable[1 - (1 - confidenceLevel) / 2];

}

std::pair<double, double> confidenceInterval::calculateInterval() {
    mean();
    interval.first = dataMean - criticalZ * std::sqrt(populationVariance) / std::sqrt(data.size());
    interval.second = dataMean + criticalZ * std::sqrt(populationVariance) / std::sqrt(data.size());
    intervalLength = std::abs(interval.first - interval.second);
    return interval;
}

void confidenceInterval::mean() {
    dataMean = 0.0;
    for (auto val: data) {
        dataMean += val;
    }
    dataMean /= data.size();
}


std::pair<double, double> confidenceInterval::run() {
    return calculateInterval();
}

confidenceIntervalT::confidenceIntervalT(std::vector<double> &data, double confidenceLevel) : data(data),
                                                                                              confidenceLevel(
                                                                                                      confidenceLevel) {
    tTableScore = createTTable();
    criticalT = tTableScore.second.lower_bound(1 - (1 - confidenceLevel) / 2)->second.lower_bound(
            data.size() - 1)->second;
}

void confidenceIntervalT::mean() {
    dataMean = 0.0;
    for (auto val: data) {
        dataMean += val;
    }
    dataMean /= data.size();
}

void confidenceIntervalT::variance() {
    dataVariance = 0.0;
    for (auto val: data) {
        dataVariance += std::pow(val - dataMean, 2);
    }
    dataVariance /= data.size() - 1;
}

std::pair<double, double> confidenceIntervalT::calculateInterval() {
    mean();
    variance();
    interval.first = dataMean - criticalT * (std::sqrt(dataVariance) / std::sqrt(data.size() - 1));
    interval.second = dataMean + criticalT * (std::sqrt(dataVariance) / std::sqrt(data.size() - 1));
    intervalLength = std::abs(interval.first - interval.second);
    return interval;
}

std::pair<double, double> confidenceIntervalT::run() {
    return calculateInterval();
}



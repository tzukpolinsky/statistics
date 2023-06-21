//
// Created by tzuk on 6/18/23.
//

#include "Ztests.h"

Ztests::Ztests(std::vector<double> &data, double populationMean, double populationVariance, double confidenceLevel,
               int testType)
        : data(data), size(data.size()), populationMean(populationMean), populationVariance(populationVariance),
          testType(testType) {
    zScoreTable = createZTable();
    if (confidenceLevel < 0.5) {
        confidenceLevel = 1 - confidenceLevel;
    }
    this->confidenceLevel = confidenceLevel;
}

void Ztests::calculateStatisticZ() {
    mean();
    statisticsZ = std::abs((dataMean - populationMean) / (std::sqrt(populationVariance) / std::sqrt(size)));
    result = statisticsZ >= getCriticalZ();
}

void Ztests::mean() {
    dataMean = 0.0;
    for (auto d: data) {
        dataMean += d;
    }
    dataMean /= size;
}

bool Ztests::run() {
    calculateStatisticZ();
    return result;
}

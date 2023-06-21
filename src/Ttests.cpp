//
// Created by tzuk on 6/18/23.
//

#include "Ttests.h"


// For one-sided test


Ttests::Ttests(std::vector<std::vector<double>> &data, int testType, double confidenceLevel, bool isPaired,
               bool differentVariances,
               std::vector<double> populationMean) : data(data),
                                                     testType(testType), populationMean(populationMean),
                                                     confidenceLevel(confidenceLevel), isPaired(isPaired),
                                                     pairedTtestCantBePreformed(false),
                                                     differentVariances(differentVariances) {
    bool sameSize = true;
    singleTtestCantBePreformed = populationMean[0] == std::numeric_limits<double>::max();
    for (int i = 1; i < data.size(); ++i) {
        sameSize = sameSize && data[i - 1].size() == data[i].size();
        if (i > populationMean.size()) {
            singleTtestCantBePreformed = true;
        }
        singleTtestCantBePreformed =
                !singleTtestCantBePreformed && populationMean[i] == std::numeric_limits<double>::max();
    }
    if (isPaired && !sameSize && singleTtestCantBePreformed) {
        pairedTtestCantBePreformed = true;
        std::cout
                << "paired T tests for different size sample without giving general population difference mean cannot be held"
                << std::endl;
        return;
    }
    tTableScore = createTTable();

}

void Ttests::mean() {
    means.clear();
    for (auto &dim: data) {
        means.emplace_back(0);
        for (auto value: dim) {
            means.back() += value;
        }
        means.back() /= dim.size();
    }
}


void Ttests::variance() {
    variances.clear();
    for (auto &dim: data) {
        variances.emplace_back(0);
        for (int i = 0; i < dim.size(); ++i) {
            variances.back() += std::pow(dim[i] - means[i], 2);
        }
        variances.back() /= dim.size() - 1;
    }
}

void Ttests::calculateStatisticsT() {

    statisticsTs.clear();
    if (!singleTtestCantBePreformed) {
        mean();
        variance();
        calculateStatisticsTTestWithKnownPopulationMean();
        calculateStatisticsTestsPowers(rawMeanDimValues);
        calculateStatisticsTestsSignificance(rawMeanDimValues);

    }
    if (isPaired && !pairedTtestCantBePreformed) {
        calculateStatisticsPairedTTests();
        calculateStatisticsTestsPowers(rawMeanDiffDimValues);
        calculateStatisticsTestsSignificance(rawMeanDiffDimValues);
    } else if (!differentVariances) {
        calculateStatisticsNonPairedTTests();
        calculateStatisticsTestsPowers(rawMeanDiffDimValues);
        calculateStatisticsTestsSignificance(rawMeanDiffDimValues);

    } else {

    }
}

void Ttests::calculateStatisticsTTestWithKnownPopulationMean() {
    for (int i = 0; i < variances.size(); ++i) {
        double stdev = std::sqrt(variances[i]);
        statisticsTs.emplace_back(
                (means[i] - populationMean[i]) / (stdev / std::sqrt(data[i].size() - 1)));
        double criticalTValue = getCriticalT(data[i].size() - 1);
        rawMeanDimValues.emplace_back(criticalTValue * stdev / (std::sqrt(data[i].size() - 1)) + populationMean[i]);
        results.emplace_back(std::abs(statisticsTs.back()) >= criticalTValue);
    }
}

void Ttests::calculateStatisticsTestsPowers(std::vector<double> &testResults) {
    for (int i = 0; i < testResults.size(); i++) {
        int df = data[i].size() - 1;
        if (testType == 0) {
            bool isSmaller = false;
            for (auto &[cl, map]: tTableScore.second) {
                if (!isSmaller) {
                    isSmaller = map[df] > testResults[i];
                } else {
                    if (map[df] < testResults[i]) {
                        testsPowers.emplace_back(1 - cl);
                        break;
                    }
                }
            }
        }
    }
}

void Ttests::calculateStatisticsPairedTTests() {
    for (int i = 0; i < data.size(); ++i) {
        for (int j = i + 1; j < data.size(); ++j) {
            calculateStatisticsPairedTTest(data[i], data[j], populationMean[i]);
        }
    }
}

void Ttests::calculateStatisticsPairedTTest(std::vector<double> &data1, std::vector<double> &data2,
                                            double populationDifferenceMean) {
    std::vector<double> differences;
    double averageDifference = 0.0;
    for (int i = 0; i < data1.size(); ++i) {
        double diff = data1[i] - data2[i];
        differences.emplace_back(diff);
        averageDifference += diff;
    }
    averageDifference /= differences.size();
    double differenceVariance = 0.0;
    for (auto &diff: differences) {
        differenceVariance += std::pow(diff - averageDifference, 2);
    }
    differenceVariance /= differences.size() - 1;
    double statisticalT = std::abs((averageDifference - populationDifferenceMean) /
                                   (std::sqrt(differenceVariance) / std::sqrt(differences.size())));
    double criticalT = getCriticalT(data1.size() - 1);
    results.emplace_back(criticalT < statisticalT);
    statisticsTs.emplace_back(statisticalT);
    rawMeanDiffDimValues.emplace_back(
            criticalT * std::sqrt(differenceVariance) / std::sqrt(differences.size()) + populationDifferenceMean);
}

void Ttests::calculateStatisticsNonPairedTTests() {
    mean();
    variance();
    for (int i = 0; i < data.size(); ++i) {
        for (int j = i + 1; j < data.size(); ++j) {
            calculateStatisticsNonPairedTTest(i, j);
        }

    }
}

void Ttests::calculateStatisticsNonPairedTTestsWithDifferentVariance() {
    mean();
    variance();
    for (int i = 0; i < data.size(); ++i) {
        for (int j = i + 1; j < data.size(); ++j) {
            calculateStatisticsNonPairedTTestWithDifferentVariances(i, j);
        }

    }
}

void Ttests::calculateStatisticsNonPairedTTest(int i, int j) {
    double pulledVariance = (double(data[i].size()) * variances[i] + double(data[j].size()) * variances[j]) /
                            double(data[i].size() + data[j].size() - 2);
    double differenceVariance =
            std::sqrt(pulledVariance) * std::sqrt(1 / double(data[i].size() + 1 / double(data[j].size())));
    double statisticsT = std::abs(means[i] - means[j] - (populationMean[i] - populationMean[j])) / differenceVariance;
    double criticalT = getCriticalT(data[i].size() + data[j].size() - 2);
    results.emplace_back(statisticsT > criticalT);
    rawMeanDiffDimValues.emplace_back(
            criticalT * std::sqrt(pulledVariance) / std::sqrt(data[i].size() + data[j].size()) +
            (populationMean[i] - populationMean[j]));

}

void Ttests::calculateStatisticsNonPairedTTestWithDifferentVariances(int i, int j) {
    double joinedVariance = std::sqrt(variances[i] / double(data[i].size()) + variances[j] / double(data[j].size()));
    double statisticsT = std::abs(means[i] - means[j] - (populationMean[i] - populationMean[j])) / joinedVariance;
    int df = std::floor(std::pow(variances[i] / double(data[i].size()) + variances[j] / double(data[j].size()), 2));
    double criticalT = getCriticalT(data[i].size() + data[j].size() - 2);
    results.emplace_back(statisticsT > criticalT);
    rawMeanDiffDimValues.emplace_back(
            criticalT * joinedVariance / std::sqrt(data[i].size() + data[j].size()) +
            (populationMean[i] - populationMean[j]));

}

void Ttests::calculateStatisticsTestsSignificance(std::vector<double> &testResults) {
    for (int i = 0; i < testResults.size(); ++i) {
        testsSignificance.emplace_back(
                std::sqrt((std::pow(testResults[i], 2) / (std::pow(testResults[i], 2) + data[i].size() - 2))));
    }
}

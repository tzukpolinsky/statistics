//
// Created by tzuk on 6/22/23.
//

#include "WilcoxonRankedTest.h"

double WilcoxonRankedTest::getCriticalValue() {
    if (dataPaired.empty()) {
        return double(size1 * size2) / 2 - getCriticalZ() * sqrt(double(size1 * size2 * (size1 + size2 + 1)) / 12);
    }
    return (double(size * (size + 1))) / 2 -
           getCriticalZ() * std::sqrt(double(size * (size + 1) * (2 * size + 1)) / 6.0);
}

WilcoxonRankedTest::WilcoxonRankedTest(std::pair<std::vector<double>, std::vector<double>> &data,
                                       double confidenceLevel, bool isTwoSided) : dataUnpaired(data),
                                                                                  confidenceLevel(
                                                                                          confidenceLevel),
                                                                                  isTwoSided(
                                                                                          isTwoSided),
                                                                                  size1(data.first.size()),
                                                                                  size2(data.second.size()) {

    zScoreTable = createZTable();
}

WilcoxonRankedTest::WilcoxonRankedTest(std::vector<std::pair<double, double>> &data, double confidenceLevel,
                                       bool isTwoSided) : dataPaired(data),
                                                          confidenceLevel(
                                                                  confidenceLevel),
                                                          isTwoSided(
                                                                  isTwoSided), size(data.size()) {
    zScoreTable = createZTable();
}

void WilcoxonRankedTest::rank() {
    std::pair<double, double> result;
    if (dataPaired.empty()) {
        result = rankUnPaired();

    } else {
        result = rankPaired();
    }
    double testValue = result.second;
    double criticalValue = getCriticalValue();
    if (result.first < result.second) {
        testValue = result.first;
    }
    testResult = testValue < criticalValue;
}

std::pair<double, double> WilcoxonRankedTest::rankUnPaired() {
    std::vector<std::pair<bool, double>> values;
    for (auto &d: dataUnpaired.first) {
        values.emplace_back(true, d);
    }
    for (auto &d: dataUnpaired.second) {
        values.emplace_back(false, d);
    }
    std::sort(values.begin(), values.end(), [&](auto &d1, auto &d2) {
        return d1.second < d2.second;
    });
    int amountSame = 1;
    double W1 = 0.0;
    double W2 = 0.0;
    ranks = std::vector<double>(values.size());
    ranks.front() = 1;
    for (int i = 1; i < values.size(); ++i) {
        double r = i + 1;
        bool insert = true;
        if (values[i - 1].second == values[i].second) {
            amountSame += 1;
            insert = false;
        } else {
            insert = true;
        }
        if (insert) {
            auto ranksSum = createRank(i, amountSame, values);
            W1 += ranksSum.first;
            W2 += ranksSum.second;
            amountSame = 1;
        }
    }
    auto ranksSum = createRank(values.size(), amountSame, values);
    W1 += ranksSum.first;
    W2 += ranksSum.second;
    return {W1, W2};

}

std::pair<double, double> WilcoxonRankedTest::rankPaired() {
    std::vector<std::pair<bool, double>> values;
    values.reserve(dataPaired.size());
    for (auto &pair: dataPaired) {
        values.emplace_back(pair.first > pair.second, pair.first - pair.second);
    }
    std::sort(values.begin(), values.end(), [&](auto &d1, auto &d2) {
        return d1.second < d2.second;
    });
    int amountSame = 1;
    double W1 = 0.0;
    double W2 = 0.0;
    ranks = std::vector<double>(values.size());
    ranks.front() = 1;
    for (int i = 1; i < values.size(); ++i) {
        double r = i + 1;
        bool insert = true;
        if (std::abs(values[i - 1].second) == std::abs(values[i].second)) {
            amountSame += 1;
            insert = false;
        } else {
            insert = true;
        }
        if (insert) {
            auto ranksSum = createRank(i, amountSame, values);
            W1 += ranksSum.first;
            W2 += ranksSum.second;
            amountSame = 1;
        }
    }
    auto ranksSum = createRank(values.size(), amountSame, values);
    W1 += ranksSum.first;
    W2 += ranksSum.second;
    return {W1, W2};
}

std::pair<double, double>
WilcoxonRankedTest::createRank(int i, int amountSame, std::vector<std::pair<bool, double>> &values) {
    double avg = 0.0;
    std::pair<double, double> rankSum{0, 0};
    for (int j = i; j > i - amountSame; --j) {
        avg += j;
    }
    avg /= amountSame;
    for (int j = i - 1; j >= i - amountSame; --j) {
        ranks[j] = avg;
        if (values[j].first) {
            rankSum.first += avg;
        } else {
            rankSum.second += avg;
        }
    }
    return rankSum;
}

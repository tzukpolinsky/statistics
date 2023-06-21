//
// Created by tzuk on 6/20/23.
//

#include "BinomialDistribution.h"

BinomialDistribution::BinomialDistribution(int n, double successProbability) {
    if (successProbability >= 1) {
        std::cout << " probability can only be 0 < p < 1" << std::endl;
        return;
    }
    this->successProbability = successProbability;
    this->failProbability = 1 - successProbability;

    this->n = n;
    zScoreTable = createZTable();
    if (n > 30) {
        onlyNormal = true;
    } else {
        fullFactorial = factorial(n);
    }
    mean();
    variance();
    build();
}

double BinomialDistribution::calculateProbability(int i) {
    if (!onlyNormal) {

        return nChooseK(i) * std::pow(successProbability, i) * std::pow(successProbability, n - i);
    } else {
        return zScoreTable.lower_bound(calculateNormalApproximation(i))->second;
    }
}

double BinomialDistribution::calculateNormalApproximation(int i) {
    return (double(i) + 0.5 - average) / probabilityStd;
}

void BinomialDistribution::variance() {
    probabilityVariance = n * successProbability * failProbability;
    probabilityStd = std::sqrt(probabilityVariance);
}

void BinomialDistribution::mean() {
    average = n * successProbability;
}

double BinomialDistribution::nChooseK(int k) {
    unsigned long kFactorial = factorial(k);
    unsigned long kMinusNFactorial = factorial(n - k);
    return double(fullFactorial) / (double(kFactorial) * double(kMinusNFactorial));
}

unsigned long BinomialDistribution::factorial(int size) {
    unsigned long temp = 1;
    while (size > 1)
        temp = temp * size--;
    return temp;
}

void BinomialDistribution::build() {
    for (int i = 1; i <= n; ++i) {
        probabilities.emplace_back(calculateProbability(i));
        normalProbabilities.emplace_back(calculateNormalApproximation(i));
    }
}

double BinomialDistribution::getProbabilityToOutcome(int i, bool normal) {
    double probability = 0.0;
    if (normal) {
        double normalProb = normalProbabilities[i];
        if (normalProb < 0.5) {
            normalProb = 1 - normalProb;
            probability += 1 - zScoreTable.lower_bound(normalProb)->second;

        } else {
            probability += zScoreTable.lower_bound(normalProb)->second;
        }

    } else {
        for (int j = 0; j < i; ++j) {
            probability += probabilities[j];
        }
    }
    return probability;
}

double BinomialDistribution::getProbabilityFromOutcome(int i, bool normal) {
    double probability = 0.0;
    if (normal) {
        double normalProb = normalProbabilities[i];
        if (normalProb < 0.5) {
            normalProb = 1 - normalProb;
            probability += zScoreTable.lower_bound(normalProb)->second;

        } else {
            probability += 1 - zScoreTable.lower_bound(normalProb)->second;
        }

    } else {
        for (int j = i; j < n; ++j) {
            probability += probabilities[j];
        }
    }
    return probability;
}

double BinomialDistribution::getProbabilityExactOutcome(int i, bool normal) {
    double probability = 0.0;
    if (normal) {
        probability = zScoreTable.lower_bound(calculateNormalApproximation(i + 1))->second;
        -zScoreTable.lower_bound(calculateNormalApproximation(i))->second;;
    } else {
        probability += probabilities[i];
    }
    return probability;
}



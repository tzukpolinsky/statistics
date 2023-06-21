//
// Created by tzuk on 6/20/23.
//

#ifndef STATISTICS_BINOMILDISTRABUTION_H
#define STATISTICS_BINOMILDISTRABUTION_H

#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include "Tables.h"

class BinomialDistribution {
public:
    BinomialDistribution(int n, double successProbability);

    double getProbabilityToOutcome(int i ,bool normal = false);

    double getProbabilityFromOutcome(int i ,bool normal = false);

    double getProbabilityExactOutcome(int i ,bool normal = false);

private:

    void build();

    double calculateProbability(int i);

    double calculateNormalApproximation(int i);

    double nChooseK(int k);

    unsigned long factorial(int size);

    void mean();

    void variance();

    static std::map<double, double> zScoreTable;
    double successProbability;
    double failProbability;
    int n;
    double average;
    double probabilityVariance;
    double probabilityStd;
    unsigned long fullFactorial;
    std::vector<double> probabilities;
    std::vector<double> normalProbabilities;
    bool onlyNormal;
};


#endif //STATISTICS_BINOMILDISTRABUTION_H

//
// Created by tzuk on 6/26/23.
//

#ifndef SIMPLESTATISTICS_SPEARMAN_H
#define SIMPLESTATISTICS_SPEARMAN_H

#include <vector>
#include <cmath>

class Spearman {
public:
    Spearman(std::vector<double> &x, std::vector<double> &y);

    void run();

private:
    std::vector<double> rank(std::vector<double> &data);

    double mean(std::vector<double> &data);

    double variance(std::vector<double> &data, double avg);

    void calculateLinearEquation();

    void calculateCorrelation();

    double correlation;
    double meanX;
    double meanY;
    double variancex;
    double variancey;
    double slope;
    double yIntercepet;
    double meanResidual;
    double SST;
    double rsquared;
    double SSE;
    double SSR;
    double maxResidual;
    double minResidual;
    std::vector<double> residuals;
    std::vector<double> x;
    std::vector<double> xRank;
    std::vector<double> y;

    std::vector<double> yRank;

    void testResult();
};


#endif //SIMPLESTATISTICS_SPEARMAN_H

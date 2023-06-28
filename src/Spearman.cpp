//
// Created by tzuk on 6/26/23.
//

#include "Spearman.h"


void Spearman::calculateCorrelation() {
    double xSum = 0;
    double ySum = 0;
    double xySum = 0;
    double x2Sum = 0;
    double y2Sum = 0;
    for (int i = 0; i < xRank.size(); ++i) {
        xSum += xRank[i];
        ySum += yRank[i];
        xySum += xRank[i] * yRank[i];
        x2Sum += std::pow(xRank[i], 2);
        y2Sum += std::pow(yRank[i], 2);
    }
    int n = xRank.size();
    double num = (n * xySum - xSum * ySum);
    double den = std::sqrt((n * x2Sum - std::pow(xSum, 2)) * (n * y2Sum - std::pow(ySum, 2)));
    correlation = num / den;
}

std::vector<double> Spearman::rank(std::vector<double> &data) {

    int N = data.size();

    // Rank Vector
    std::vector<double> Rank_X(N);

    for (int i = 0; i < N; i++) {
        int r = 1, s = 1;
        for (int j = 0; j < i; j++) {
            if (data[j] < data[i]) r++;
            if (data[j] == data[i]) s++;
        }
        for (int j = i + 1; j < N; j++) {
            if (data[j] < data[i]) r++;
            if (data[j] == data[i]) s++;
        }
        Rank_X[i] = r + (s - 1) * 0.5;
    }
    return Rank_X;
}

Spearman::Spearman(std::vector<double> &x, std::vector<double> &y) : x(x), y(y) {

}

void Spearman::testResult() {
    residuals.reserve(x.size());
    meanResidual = 0.0;
    maxResidual = 0.0;
    minResidual = std::numeric_limits<double>::max();;
    for (int n = 0; n < x.size(); n++) {
        double yhat = yIntercepet + (slope * x[n]);
        double residual = y[n] - yhat;
        SSE += pow((yhat - meanY), 2);
        SSR += pow(residual, 2);
        residuals[n] = residual;
        if (residuals[n] > maxResidual) {
            maxResidual = residuals[n];
        }
        if (residuals[n] < minResidual) {
            minResidual = residuals[n];
        }
        meanResidual += fabsf64(residuals[n]);
    }
    meanResidual /= double(x.size());
    SST = SSR + SSE;
    rsquared =
            SSE / SST;           //Can also be obtained by r ^ 2 for simple regression (i.e. 1 independent variable)

}

void Spearman::run() {
    xRank = rank(x);
    yRank = rank(y);
    calculateCorrelation();
    meanX = mean(xRank);
    meanY = mean(yRank);
    variancex = variance(xRank, meanX);
    variancey = variance(yRank, meanY);
    calculateLinearEquation();
    testResult();
}

void Spearman::calculateLinearEquation() {
    slope = correlation * (variancey / variancex);
    yIntercepet = meanY - slope * meanX; // y =mx+b

}

double Spearman::mean(std::vector<double> &data) {
    double avg = 0;
    for (auto i: data) {
        avg += i;
    }
    avg /= data.size();
    return avg;
}

double Spearman::variance(std::vector<double> &data, double avg) {
    double variance = 0;
    for (auto i: data) {
        variance += std::pow(i - avg, 2);
    }
    variance /= data.size();
    return variance;
}


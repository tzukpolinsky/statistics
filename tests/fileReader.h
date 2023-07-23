//
// Created by tzuk on 7/6/23.
//

#ifndef SIMPLESTATISTICS_FILEREADER_H
#define SIMPLESTATISTICS_FILEREADER_H

#include <fstream>
#include <string>
#include <sstream>
std::unordered_map<int, std::vector<double>> readDataScientistsSalaryByYears(std::string fileName, int salaryIndex) {
    std::ifstream stocksData(fileName);
    std::unordered_map<int, std::vector<double>> stocks;
    std::string line;
    std::getline(stocksData, line);
    while (std::getline(stocksData, line)) {
        std::stringstream lineStream(line);
        int year;
        lineStream >>year;
        if (lineStream.peek() == ',')
            lineStream.ignore();
        for (int i = 1; i < salaryIndex; ++i) {
            std::string junk;
            lineStream >> junk;
            if (lineStream.peek() == ',')
                lineStream.ignore();
        }
        double price;
        lineStream >> price;
        if (not stocks.count(year)) {
            stocks[year] = std::vector<double>{};
        }
        stocks[year].emplace_back(price);
    }
    return stocks;
}

std::unordered_map<std::string, std::vector<double>> readMicrosoftStocksByYears(std::string fileName, int priceIndex) {
    std::ifstream stocksData(fileName);
    std::unordered_map<std::string, std::vector<double>> stocks;
    std::string line;
    std::getline(stocksData, line);
    while (std::getline(stocksData, line)) {
        std::stringstream lineStream(line);
        std::string date;
        std::getline(lineStream,date,',');
        if (lineStream.peek() == ',')
            lineStream.ignore();
        for (int i = 1; i < priceIndex; ++i) {
            std::string junk;
            lineStream >> junk;
            if (lineStream.peek() == ',')
                lineStream.ignore();
        }
        std::string year = date.substr(date.size() - 4);
        double price;
        lineStream >> price;
        if (not stocks.count(year)) {
            stocks[year] = std::vector<double>{};
        }
        stocks[year].emplace_back(price);
    }
    return stocks;
}

#endif //SIMPLESTATISTICS_FILEREADER_H

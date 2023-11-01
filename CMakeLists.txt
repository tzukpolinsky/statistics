cmake_minimum_required(VERSION 2.8)
project(simpleStatistics)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
include_directories(include)
add_library(LinearRegression src/LinearRegression.cpp)
add_library(zTests src/Ztests.cpp)
add_library(tTests src/Ttests.cpp)
add_library(confidenceInterval src/confidenceInterval.cpp)
add_library(BinomialDistribution src/BinomialDistribution.cpp)
add_library(WilcoxonRankedTest src/WilcoxonRankedTest.cpp)
add_library(Spearman src/Spearman.cpp)
add_subdirectory(tests)
install(TARGETS LinearRegression tTests zTests confidenceInterval BinomialDistribution WilcoxonRankedTest Spearman
        LIBRARY DESTINATION lib/statistics
        ARCHIVE DESTINATION lib/statistics)
install(FILES include/BinomialDistribution.h include/LinearRegression.h include/confidenceInterval.h include/Ttests.h include/Tables.h
        include/Ztests.h include/WilcoxonRankedTest.h include/Spearman.h
        DESTINATION include/statistics)
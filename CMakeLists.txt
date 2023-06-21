cmake_minimum_required(VERSION 2.8)
project(statistics)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
include_directories(include)
add_library(linearRegression src/LinearRegression.cpp)
add_library(zTests src/Ztests.cpp)
add_library(tTests src/Ttests.cpp)
add_library(confidenceInterval src/confidenceInterval.cpp)
add_library(BinomialDistribution src/BinomialDistribution.cpp)

install(TARGETS linearRegression DESTINATION /usr/local/lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION /usr/local/include/
        FILES_MATCHING PATTERN "*.h")
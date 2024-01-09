#include <iostream>
#include <vector>
#include <cmath>
#include "..\..\..\CSV Reader\csv.h"

// Function to calculate the mean of a vector
double mean(std::vector<double> v) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum / v.size();
}

// Function to calculate the variance of a vector
double variance(std::vector<double> v, double mean) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += pow(v[i] - mean, 2);
    }
    return sum / v.size();
}

// Function to calculate the covariance of two vectors
double covariance(std::vector<double> x, std::vector<double> y, double mean_x, double mean_y) {
    double sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum += (x[i] - mean_x) * (y[i] - mean_y);
    }
    return sum / x.size();
}

// Function to calculate the coefficients of the linear regression model
std::pair<double, double> coefficients(std::vector<double> x, std::vector<double> y) {
    double mean_x = mean(x);
    double mean_y = mean(y);
    double b1 = covariance(x, y, mean_x, mean_y) / variance(x, mean_x);
    double b0 = mean_y - b1 * mean_x;
    return std::make_pair(b0, b1);
}

int main() {
    std::vector<std::vector<double>> data = read_csv("wine.csv");

    // Assuming the first column is the target variable and the second column is the feature
    std::vector<double> y(data.size());
    std::vector<double> x(data.size());
    for (int i = 0; i < data.size(); i++) {
        y[i] = data[i][0];
        x[i] = data[i][1];
    }

    std::pair<double, double> coeffs = coefficients(x, y);

    std::cout << "The coefficients of the linear regression model are: " << coeffs.first << ", " << coeffs.second << std::endl;

    return 0;
}

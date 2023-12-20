#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct IrisData {
    double sepal_length;
    double petal_width;
};

// Function to read data from a string
void readData(std::vector<IrisData>& data, const std::string& dataString) {
    std::istringstream dataStream(dataString);
    std::string line;

    // Skip the header line
    std::getline(dataStream, line);

    while (std::getline(dataStream, line)) {
        std::istringstream lineStream(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(lineStream, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 5) {
            IrisData point;
            point.sepal_length = std::stod(tokens[0]);
            point.petal_width = std::stod(tokens[3]);
            data.push_back(point);
        }
    }
}

// Function to perform linear regression
void linearRegression(const std::vector<IrisData>& data, double& Co, double& C1) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    int n = data.size();

    for (const auto& d : data) {
        sum_x += d.petal_width;
        sum_y += d.sepal_length;
        sum_xy += d.sepal_length * d.petal_width;
        sum_x2 += d.petal_width * d.petal_width;
    }

    C1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    Co = (sum_y - C1 * sum_x) / n;
}

int main() {
    std::vector<IrisData> data;

    std::string dataString = "iris.csv";

    readData(data, dataString);

    double Co = 2;
    double C1 = 2;

    linearRegression(data, Co, C1);

    std::cout << "Linear Fit: sepal_length = " << Co << " + " << C1 << " * petal_width" << std::endl;

    return 0;
}

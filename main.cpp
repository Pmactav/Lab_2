#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <Eigen/Dense>
#include "functions.h"

using namespace std;
using namespace Eigen;

int main() {
    MatrixXd dataA = ReadDatatoMatrix("../obsA_2026.txt");
    MatrixXd dataB = ReadDatatoMatrix("../obsB_2026.txt");
    MatrixXd obsA = dataA.col(1);
    MatrixXd obsB = dataB.col(1);
    double range1 = obsA.maxCoeff() - obsA.minCoeff();
    double range2 = obsB.maxCoeff() - obsB.minCoeff();
    double mean1 = obsA.mean();
    double mean2 = obsB.mean();
    double var1 = obsA.colwise().squaredNorm().mean();
    double var2 = obsB.colwise().squaredNorm().mean();
    double sigma1 = obsA.colwise().norm().mean();
    double sigma2 = obsB.colwise().norm().mean();
    double meanDeviation1 = sqrt(var1/obsA.rows());
    double meanDeviation2 = sqrt(var2/obsB.rows());
    double P1 = sqrt(var1/(obsA.rows()-1));
    double P2 = sqrt(var2/(obsB.rows()-1));
    double weightedMean = (P1*mean1 + P2*mean2)/(P1+P2);
    double weightedSigma = sqrt((P1*var1 + P2*var2)/(obsA.rows()+obsB.rows()-2));
    double median1 = median(obsA,1);
    double median2 = median(obsB,1);
    cout << "Median A: " << median1 << endl;
    cout << "Median B: " << median2 << endl;
    cout << "Weighted mean: " << weightedMean << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <numeric>
#include <vector>
#include <Eigen/Dense>
#include "functions.h"

using namespace std;
using namespace Eigen;

int main() {
    MatrixXd dataA = ReadDatatoMatrix("../obsA_2026.txt"); //Read data
    MatrixXd dataB = ReadDatatoMatrix("../obsB_2026.txt");
    MatrixXd obsA = dataA.col(1);//isolate observations
    MatrixXd obsB = dataB.col(1);
    int n1 = obsA.rows();
    int n2 = obsB.rows();
    //Compute statistics
    double range1 = obsA.maxCoeff() - obsA.minCoeff();
    double range2 = obsB.maxCoeff() - obsB.minCoeff();
    double mean1 = obsA.mean();
    double mean2 = obsB.mean();
    double median1 = median(obsA);
    double median2 = median(obsB);
    double sampleSquared1 = (obsA.array() - obsA.mean()).square().sum();
    double sampleSquared2 = (obsB.array() - obsB.mean()).square().sum();
    double sigmasquared1 = sampleSquared1/(n1-1);
    double sigmasquared2 = sampleSquared2/(n2-1);
    double sigma1 = sqrt(sigmasquared1);
    double sigma2 = sqrt(sigmasquared2);
    double meanDeviation1 = sqrt(sigmasquared1/n1);
    double meanDeviation2 = sqrt(sigmasquared2/n2);
    double P1 = 1.0/sigmasquared1;
    double P2 = 1.0/sigmasquared2;
    double weightedMean = (P1*mean1 + P2*mean2)/(P1+P2);
    double weightedSigma = sqrt(1.0/(P1+P2));
    //Calculate CI
    double z95 = 1.96; //both samples >30 so used z table value
    double confidenceIntervalLow  = weightedMean - z95*weightedSigma;
    double confidenceIntervalHigh = weightedMean + z95*weightedSigma;
    //residuals
    double z99 = 2.576;
    double res99A = z99 * sigma1;
    double res99B = z99 * sigma2;
    //Print results
    cout << setprecision(4);
    cout << "Na," << n1 << ",Nb," << n2 << "\n";
    cout << "Stat,Obs A,Obs B\n";
    cout << "Median," << median1 << "," << median2 << "\n";
    cout << "Range," << range1 << "," << range2 << "\n";
    cout << "Mean," << mean1 << "," << mean2 << "\n";
    cout << "Std Dev," << sigma1 << "," << sigma2 << "\n";
    cout << "Std Dev Mean," << meanDeviation1 << "," << meanDeviation2 << "\n";
    cout << "Weighted Mean," << weightedMean << ",\n";
    cout << "Weighted Std Dev," << weightedSigma << ",\n";
    cout << "CI 95%," << confidenceIntervalLow << "," << confidenceIntervalHigh << "\n";
    cout << "Res 99% A," << res99A << "," << res99B << "\n";

    //Task 2
    MatrixXd weight = ReadDatatoMatrix("../weight_2026.txt");
    MatrixXd height = ReadDatatoMatrix("../height_2026.txt");
    MatrixXd speed = ReadDatatoMatrix("../speed_2026.txt");
    MatrixXd goals = ReadDatatoMatrix("../goals_2026.txt");

    cout << weight.rows() << endl;
    cout << height.rows() << endl;
    cout << speed.rows() << endl;
    cout << goals.rows() << endl;
    return 0;
}

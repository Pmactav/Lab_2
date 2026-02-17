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
    int nA = obsA.rows();
    int nB = obsB.rows();

    //Compute stats
    double rangeA = obsA.maxCoeff() - obsA.minCoeff();
    double rangeB = obsB.maxCoeff() - obsB.minCoeff();
    double meanA = obsA.mean();
    double meanB = obsB.mean();
    VectorXd resA = obsA.array() - meanA;
    VectorXd resB = obsB.array() - meanB;
    double medianA = median(obsA);
    double medianB = median(obsB);
    double sampleSquaredA = (obsA.array() - obsA.mean()).square().sum();
    double sampleSquaredB = (obsB.array() - obsB.mean()).square().sum();
    double varA = sampleSquaredA/(nA-1);
    double varB = sampleSquaredB/(nB-1);
    double stDevA = sqrt(varA);
    double stDevB = sqrt(varB);
    double meanDeviationA = sqrt(varA/nA);
    double meanDeviationB = sqrt(varB/nB);
    double P1 = 1.0/varA;
    double P2 = 1.0/varB;
    double weightedMean = (P1*meanA + P2*meanB)/(P1+P2);
    double weightedSigma = sqrt(1.0/(P1+P2));

    //Residual stats
    double resRangeA = resA.maxCoeff() - resA.minCoeff();
    double resRangeB = resB.maxCoeff() - resB.minCoeff();
    double resSumA = resA.sum();
    double resSumB = resB.sum();
    double resMeanA = resA.mean();
    double resMeanB = resB.mean();
    double resVarA = (resA.array().square().sum())/(nA-1);
    double resVarB = (resB.array().square().sum())/(nB-1);
    double resStDevA = sqrt(resVarA);
    double resStDevB = sqrt(resVarB);
    double resmedianA = median(resA);
    double resmedianB = median(resB);

    //Calculate CI
    double z95 = 1.96; //both samples >30 so used z table value
    double confidenceIntervalLow  = weightedMean - z95*weightedSigma;
    double confidenceIntervalHigh = weightedMean + z95*weightedSigma;

    //residuals CI
    double z99 = 2.576;
    double res99HighA = resMeanA + z99*resStDevA/sqrt(nA);
    double res99HighB = resMeanB + z99*resStDevB/sqrt(nB);
    double res99LowA = resMeanA - z99*resStDevA/sqrt(nA);
    double res99LowB = resMeanB - z99*resStDevB/sqrt(nB);

    //Print result
    /*
    cout << setprecision(5);
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
    */

    //Task 2
    MatrixXd weight = ReadDatatoMatrix("../weight_2026.txt");
    MatrixXd height = ReadDatatoMatrix("../height_2026.txt");
    MatrixXd speed = ReadDatatoMatrix("../speed_2026.txt");
    MatrixXd goals = ReadDatatoMatrix("../goals_2026.txt");

    VectorXd weightStats = stats(weight);
    VectorXd heightStats = stats(height);
    VectorXd speedStats  = stats(speed);
    VectorXd goalsStats  = stats(goals);

    /*
    cout << "\tMean\tVariance\tDeviation\n";
    printStats("Weight", weightStats);
    printStats("Height", heightStats);
    printStats("Speed",  speedStats);
    printStats("Goals",  goalsStats);
    */

    MatrixXd results(12, 2);

    results <<
    nA, nB,
    rangeA, rangeB,
    meanA, meanB,
    medianA, medianB,
    varA, varB,
    stDevA, stDevB,
    meanDeviationA, meanDeviationB,
    resSumA, resSumB,
    resMeanA, resMeanB,
    resStDevA, resStDevB,
    res99LowA, res99LowB,
    res99HighA, res99HighB;

    ofstream weightedResults("task1_weighted.csv");
    weightedResults << "Statistic,Value\n";
    weightedResults << "WeightedMean, " << weightedMean << "\n";
    weightedResults << "WeightedStdDev, " << weightedSigma << "\n";
    weightedResults << "CI95Low,"  << confidenceIntervalLow  << "\n";
    weightedResults << "CI95High," << confidenceIntervalHigh << "\n";
    weightedResults.close();

    WriteMatrixToFile(results, "task1_results.csv", 6);
    WriteMatrixToFile(obsA, "obsA.csv", 6);
    WriteMatrixToFile(obsB, "obsB.csv", 6);
    WriteMatrixToFile(resA, "residualsA.csv", 6);
    WriteMatrixToFile(resB, "residualsB.csv", 6);

    return 0;
}

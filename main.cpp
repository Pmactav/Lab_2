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

    //Task 2
    //this could be a loop if time
    MatrixXd weight = ReadDatatoMatrix("../weight_2026.txt");
    MatrixXd height = ReadDatatoMatrix("../height_2026.txt");
    MatrixXd speed = ReadDatatoMatrix("../speed_2026.txt");
    MatrixXd goals = ReadDatatoMatrix("../goals_2026.txt");
    //build full matrix
    int n = weight.rows();
    MatrixXd V(n, 4);
    V.col(0) = weight;
    V.col(1) = height;
    V.col(2) = speed;
    V.col(3) = goals;
    //calculate var covar matrix
    VectorXd mean = V.colwise().mean();
    MatrixXd centered = V.rowwise() - mean.transpose();
    MatrixXd C = (centered.transpose() * centered) / (n - 1);
    VectorXd stddev = C.diagonal().cwiseSqrt();
    MatrixXd R = C.array()/(stddev * stddev.transpose()).array();

    //separate vectors to compute stats, could be a loop if time
    VectorXd weightStats = stats(weight);
    VectorXd heightStats = stats(height);
    VectorXd speedStats  = stats(speed);
    VectorXd goalsStats  = stats(goals);
    //sace to csv, should make a function or loop
    ofstream results("task1_results.csv");
    results << "Statistic,ObsA,ObsB\n";
    writeRow(results, "N", nA, nB);
    writeRow(results, "Range", rangeA, rangeB);
    writeRow(results, "Mean", meanA, meanB);
    writeRow(results, "Median", medianA, medianB);
    writeRow(results, "Variance", varA, varB);
    writeRow(results, "StdDev", stDevA, stDevB);
    writeRow(results, "meanDeviation", meanDeviationA, meanDeviationB);

    writeRow(results, "ResidualSum", resSumA, resSumB);
    writeRow(results, "ResidualMean", resMeanA, resMeanB);
    writeRow(results, "ResidualStdDev", resStDevA, resStDevB);
    writeRow(results, "ResidualCI99Low", res99LowA, res99LowB);
    writeRow(results, "ResidualCI99High", res99HighA, res99HighB);
    results.close();

    ofstream weightedResults("task1_weighted.csv");
    weightedResults << "Statistic,Value\n";
    weightedResults << "WeightedMean, " << weightedMean << "\n";
    weightedResults << "WeightedStdDev, " << weightedSigma << "\n";
    weightedResults << "CI95Low,"  << confidenceIntervalLow  << "\n";
    weightedResults << "CI95High," << confidenceIntervalHigh << "\n";
    weightedResults.close();

    WriteMatrixToFile(obsA, "obsA.csv", 6);
    WriteMatrixToFile(obsB, "obsB.csv", 6);
    WriteMatrixToFile(resA, "residualsA.csv", 6);
    WriteMatrixToFile(resB, "residualsB.csv", 6);
    WriteMatrixToFile(C, "covariance.csv", 6);
    WriteMatrixToFile(R, "correlation.csv", 6);

    return 0;
}

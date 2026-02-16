//
// Created by Peter on 2/4/2026.
//
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

MatrixXd ReadDatatoMatrix(const std::string &filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "ERROR: Could not open file " << filename << "\n";
        return MatrixXd(0,0);}
    vector<vector<double>> data;
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<double> row;
        double value;
        while (ss >> value) {row.push_back(value);}
        if (!row.empty())data.push_back(row);}
    if (data.empty())
        return MatrixXd(0,0);
    int rows = data.size();
    int cols = data[0].size();
    MatrixXd M(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            M(i,j) = data[i][j];
    return M;
}


void WriteMatrixToFile(const MatrixXd &Mat, const string& filename, unsigned int precision){
    ofstream out(filename, ios::out);
    if (out.fail()){
        cout << "Could not open output file " << filename << endl;
        exit(1);
    }
    out << fixed << setprecision(precision);
    for (int i = 0; i < Mat.rows(); ++i){
        for (int j = 0; j < Mat.cols(); ++j){
            out << Mat(i, j);
            if (j != Mat.cols() - 1)
                out << " ";
        }
        out << endl;
    }
    out.close();
}

double median(const MatrixXd& M) {
    int n = M.rows();
    if (n % 2 == 0) {return (M(n/2 - 1, 0) + M(n/2, 0)) / 2.0;}
    else {return M(n/2, 0);}
}

VectorXd stats(const MatrixXd &M) {
    VectorXd out(3);
    double mean = M.mean();
    double sigmaSquared =(M.array()-mean).square().sum()/(M.rows() - 1);
    double sigma = sqrt(sigmaSquared);
    out << mean, sigmaSquared, sigma;
    return out;
}

void printStats(const string& name, const VectorXd& s) {
    cout << setw(2) << name
         << setw(9) << s(0)
         << setw(9) << s(1)
         << setw(9) << s(2)
         << endl;
}

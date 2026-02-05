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
        return MatrixXd(0, 2);
    }
    vector<Vector2d> rows;
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        double t, l;
        if (ss >> t >> l) {
            rows.emplace_back(t, l);
        }
    }
    infile.close();
    MatrixXd M(rows.size(), 2);
    for (int i = 0; i < static_cast<int>(rows.size()); ++i) {
        M.row(i) = rows[i];
    }
    return M;
}

MatrixXd DesignMatrix(const MatrixXd& M, double omega) {
    MatrixXd A(M.rows(),3);
    for (int i = 0; i < M.rows(); ++i) {
        A(i,0) = sin(M(i,0)*omega);
        A(i,1) = cos(M(i,0)*omega);
        A(i,2) = 1;
    }
    return A;
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

double median(const MatrixXd& M, int col) {
    int n = M.rows();

    if (n % 2 == 0) {return (M(n/2 - 1, 0) + M(n/2, 0)) / 2.0;}
    else {return M(n/2, 0);}
}
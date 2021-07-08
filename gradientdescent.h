#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

class GradientDescent
{
public:
    vector<double> X;
    vector<double> Y;

    GradientDescent(vector<double> x, vector<double> y);
    static double MSE     (vector<double> x, vector<double> X, vector<double> Y);
    static double RMSE    (vector<double> x, vector<double> X, vector<double> Y);
    static double MAE     (vector<double> x, vector<double> X, vector<double> Y);
    double phi     (double alpha, vector<double> xk, vector<double> dk);
    double deff_phi(double alpha, vector<double> xk, vector<double> dk);
    double armijo  (vector<double> xk, vector<double> dk, double (*loss_func)(vector<double> x, vector<double> X, vector<double> Y));
    double wolfe   (vector<double> xk, vector<double> dk);
    double norme   (vector<double> U);
    vector<double> grad_f  (vector<double> x);
    vector<double> gradient(vector<double> w, double (*loss_func)(vector<double> w, vector<double> X, vector<double> Y));
    vector<double> gradientMethod(double deta, vector<double> xk, double (*loss_func)(vector<double> x, vector<double> X, vector<double> Y));
};

#endif // GRADIENTDESCENT_H

#include "gradientdescent.h"
#include "operators.h"

GradientDescent::GradientDescent(vector<double> X, vector<double> Y)
{
    this->X = X;
    this->Y = Y;
}

double GradientDescent::MSE(vector<double> W, vector<double> X, vector<double> Y)
{
    double Ls = 0;
    for(int i=0; i<50; i++)
        Ls += pow(Y[i] - X[i]*W[0] - W[1] ,2);

    return Ls/X.size();
}

double GradientDescent::RMSE(vector<double> W, vector<double> X, vector<double> Y)
{
    return sqrt(MSE(W,X,Y));
}

double GradientDescent::MAE(vector<double> W, vector<double> X, vector<double> Y)
{
    double Ls = 0;
    for(int i=0; i<50; i++)
        Ls += abs(Y[i] - X[i]*W[0] - W[1]);

    return Ls/X.size();
}

double GradientDescent::armijo(vector<double> xk, vector<double> dk, double (*loss_func)(vector<double> x, vector<double> X, vector<double> Y))
{
    double alpha = 1;
    double stp = 0.25*alpha*gradient(xk,loss_func)*dk;
    while(loss_func(xk + alpha*dk,X,Y) - loss_func(xk,X,Y) > stp){
        alpha = alpha/2;
        stp = 0.25*alpha*gradient(xk,loss_func)*dk;
    }
    return alpha;
}

double GradientDescent::norme(vector<double> U)
{
    double N=0;
    for (int i = 0; i <(int)U.size(); i++)
        N = N + U[i]*U[i];
    return sqrt(N);
}

vector<double> GradientDescent::gradient(vector<double> w, double (*loss_func)(vector<double> w, vector<double> X, vector<double> Y))
{
    vector<double> grad(w.size() , 0);

    vector<double> wk;
    double h = 1e-10;
    for(int i=0; i<(int)w.size(); i++){
        wk       = w;
        wk  [i] += h;
        grad[i]  = (loss_func(wk,X,Y)-loss_func(w,X,Y))/h;
    }
    return grad;
}

vector<double> GradientDescent::gradientMethod(double deta, vector<double> xk, double (*loss_func)(vector<double> x, vector<double> X, vector<double> Y))
{
    vector<double> gk = gradient(xk,loss_func);
    double alpha;
    int k=0;
    while(norme(gk) > deta && k<1000)
    {
        cout<<k<<"-"<<loss_func(xk,X,Y)<<","<<endl;
        alpha = armijo(xk,-1*gk,loss_func);
        xk = xk - alpha*gk;
        gk = gradient(xk,loss_func);
        k++;
    }
    return xk;
}

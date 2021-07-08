#include "dradientdescentmultiple.h"
#include "operators.h"

DradientDescentMultiple::DradientDescentMultiple(vector<vector<double>> X, vector<double> Y)
{
    this->X = X;
    this->Y = Y;
}

double DradientDescentMultiple::f(vector<double> W)
{
    double Ls = 0, produit = 0;
    for(int i=0; i<(int)X.size(); i++)
    {
        for(int j=0; j<(int)X[i].size(); j++)
        {
            produit +=X[i][j]*W[j];
        }
        produit += W[X[i].size()];
        Ls += pow(Y[i] - produit,2);
    }

    return Ls/X.size();
}

double DradientDescentMultiple::phi(double alpha, vector<double> xk, vector<double> dk)
{
    return f(xk + alpha * dk);
}

double DradientDescentMultiple::deff_phi(double alpha, vector<double> xk, vector<double> dk)
{
    return ( phi(alpha + 0.01,xk,dk) - phi(alpha - 0.01,xk,dk) )*50;
}

double DradientDescentMultiple::armijo(vector<double> xk, vector<double> dk)
{
    double alpha = 1;
    double X = 0.25*alpha*grad_f(xk)*dk;
    while(f(xk + alpha*dk) - f(xk) > X){
        alpha = alpha/2;
        X = 0.25*alpha*grad_f(xk)*dk;
    }
    return alpha;
}

double DradientDescentMultiple::wolfe(vector<double> xk, vector<double> dk)
{
    double alpha = 1, ak = 0, bk = 1000;
    int k=0;

    while(f(xk + alpha*dk) > 0.1*deff_phi(alpha,xk,dk)*alpha +f(xk) && deff_phi(alpha,xk,dk) < 0.7*deff_phi(0,xk,dk) && k<100){
        if(f(xk + alpha*dk) > 0.1*deff_phi(alpha,xk,dk)*alpha +f(xk)){
            bk = alpha;
            ak = alpha;
        }
        else if(f(xk + alpha*dk) <= 0.1*deff_phi(alpha,xk,dk)*alpha +f(xk) && deff_phi(alpha,xk,dk) < 0.7*deff_phi(0,xk,dk)){
            bk = alpha;
            ak = alpha;
        }

        if(bk == 0)
            alpha = ak + 10;
        else
            alpha = (ak + bk)/2;
        k++;
    }
    return alpha;
}

double DradientDescentMultiple::norme(vector<double> U)
{
    double N=0;
    for (int i = 0; i <(int)U.size(); i++)
        N = N + U[i]*U[i];
    return sqrt(N);
}

vector<double> DradientDescentMultiple::grad_f(vector<double> x)
{
    vector<double> grad(x.size() , 0);

    vector<double> xk;
    double h = 1e-10;
    for(int i=0; i<(int)x.size(); i++){
        xk       = x;
        xk  [i] += h;
        grad[i]  = (f(xk)-f(x))/h;
    }
    return grad;
}

vector<double> DradientDescentMultiple::gradientMethod(double deta, vector<double> xk)
{
    vector<double> gk = grad_f(xk);
    double alpha;
    int k=0;
    while(norme(gk) > deta && k<1000)
    {
        cout<<f(xk)<<","<<endl;
        alpha = armijo(xk,-1*gk);
        xk = xk - alpha*gk;
        gk = grad_f(xk);
        k++;
    }
    return xk;
}

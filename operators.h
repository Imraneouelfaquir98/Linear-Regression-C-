#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>

using namespace std;

double                  operator*(const vector<double> & U       , const vector<double>        & V    );
vector <double>         operator*(const double &alpha            , const vector<double>        & U    );
vector <double>         operator*(const vector<double> & U       , const double                & alpha);
vector <vector<double>> operator*(const vector<vector<double>>& U, const vector<vector<double>>& V    );
vector <vector<double>> operator*(const double &alpha            , const vector<vector<double>>& U    );
vector <vector<double>> operator*(const vector<vector<double>>& U, const double                & alpha);
vector <double>         operator/(const vector<double> & U       , const double                & m    );
vector <vector<double>> operator/(const vector<vector<double>>& U, const double                & m    );
vector <vector<double>> operator/(const vector<vector<double>>& U, const vector<vector<double>>& m    );
vector <double>         operator-(const vector<double> & U       , const vector<double>        & V    );
vector <vector<double>> operator-(const vector<vector<double>>& U, const vector<vector<double>>& V    );
vector <double>         operator+(const vector<double> & U       , const vector<double>        & V    );
vector <vector<double>> operator+(const vector<vector<double>>& U, const vector<vector<double>>& V    );
vector <vector<double>> T        (const vector<vector<double>>& U);

#endif // OPERATORS_H

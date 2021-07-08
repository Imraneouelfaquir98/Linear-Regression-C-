#include "operators.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

double operator*(const vector<double>& U, const vector<double>& V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            double produit = 0;
            for(int i = 0 ; i < U.size() ; i++)
                produit += U[i] * V[i];
            return produit;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return 0;
    }
}

vector<double> operator*(const double &alpha, const vector<double>& U){
    vector<double> W(U.size() , 0);
    for(int i = 0 ; i < U.size() ; i++)
        W[i] = alpha*U[i];
    return W;
}


vector<double> operator*(const vector<double>& U, const double &alpha){
    vector<double> W(U.size() , 0);
    for(int i = 0 ; i < U.size() ; i++)
                W[i] = alpha*U[i];
    return W;
}

vector <vector<double>> operator*(const vector<vector<double>>& U, const vector<vector<double>>& V){
    vector <vector<double>> W(U.size() , vector<double>(V[0].size(),0));
    try{
        if(U[0].size() != V.size()){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++){
                for(int j = 0 ; j < V[0].size() ; j++){
                    double pivot;
                    for(int k = 0 ; k < U[0].size() ; k++)
                        W[i][j] += U[i][k] * V[k][j];
                }
            }
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

vector <vector<double>> operator*(const double &alpha, const vector<vector<double>>& U){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    for(int i = 0 ; i < U.size() ; i++)
        for(int j = 0 ; j < U[0].size() ; j++)
                W[i][j] = alpha*U[i][j];
    return W;
}

vector <vector<double>> operator*(const vector<vector<double>>& U, const double &alpha){
    return alpha*U;
}

vector<double> operator/(const vector<double> & U, const double &m){
    try{
        if( m == 0){
            throw string("ERREUR : can not devise with zero !");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++)
                        W[i] = U[i]/m;
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}

vector <vector<double>> operator/(const vector<vector<double>>& U, const double &m){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if( m == 0){
            throw string("ERREUR : can not devise with zero !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++)
                for(int j = 0 ; j < U[0].size() ; j++)
                        W[i][j] = U[i][j]/m;
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

vector <vector<double>> operator/(const vector<vector<double>>& U, const vector<vector<double>>& m){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if(m[0].size() > 1 || m.size() > 1){
            throw string("ERREUR : can not devise with vector !");
        }
        else if( m[0][0] == 0){
            throw string("ERREUR : can not devise with zero !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++)
                for(int j = 0 ; j < U[0].size() ; j++)
                        W[i][j] = U[i][j]/m[0][0];
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

vector<double> operator-(const vector<double> & U, const vector<double> & V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !1");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++){
                    W[i] = U[i] - V[i];
            }
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}

vector <vector<double>> operator-(const vector<vector<double>>& U, const vector<vector<double>>& V){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if(U.size() != V.size() || U[0].size() != V[0].size() ){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++){
                for(int j = 0 ; j < U[0].size() ; j++){
                    W[i][j] = U[i][j] - V[i][j];
                }
            }
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

vector<double> operator+(const vector<double> & U, const vector<double> & V){
    try{
        if(U.size() != V.size()){
            throw string("ERREUR : Dimension incompatible !2");
        }
        else{
            vector<double> W(U.size() , 0);
            for(int i = 0 ; i < U.size() ; i++){
                    W[i] = U[i] + V[i];
            }
            return W;
        }
    }
    catch(string const& chaine){
        cerr << chaine << endl;
        vector<double> W (U.size(), 0);
        return W;
    }
}

vector <vector<double>> operator+(const vector<vector<double>>& U, const vector<vector<double>>& V){
    vector <vector<double>> W(U.size() , vector<double>(U[0].size(),0));
    try{
        if(U.size() != V.size() || U[0].size() != V[0].size() ){
            throw string("ERREUR : Dimension incompatible !");
        }
        else{
            for(int i = 0 ; i < U.size() ; i++){
                for(int j = 0 ; j < U[0].size() ; j++){
                    W[i][j] = U[i][j] + V[i][j];
                }
            }
            return W;
        }
    }
    catch(string const& chaine){
       cerr << chaine << endl;
       return W;
    }
}

// Transposé
vector <vector<double>> T(const vector<vector<double>>& U){
    vector <vector<double>> W(U[0].size() , vector<double>(U.size(),0));
    for(int i = 0 ; i < U.size() ; i++){
        for(int j = 0 ; j < U[0].size() ; j++){
            W[j][i] = U[i][j];
        }
    }
    return W;
}

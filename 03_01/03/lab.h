#ifndef LAB_H_INCLUDED
#define LAB_H_INCLUDED

#include<vector>
#include <functional>
#include <iostream>
using namespace std;

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations
                            );

vector<double> simulated_annealing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain,
                                   vector<double> p0, int iterations, function<vector<double>(vector<double>)> N,function<double(int)> T);



std::ostream& operator<<(ostream& o, vector<double> v);
#endif // LAB_H_INCLUDED

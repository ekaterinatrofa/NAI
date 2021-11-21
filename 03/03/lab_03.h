#ifndef LAB_03_H_INCLUDED
#define LAB_03_H_INCLUDED

#include<vector>
#include <functional>

using namespace std;

int sum(int a, int b);


vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations);
#endif // LAB_03_H_INCLUDED

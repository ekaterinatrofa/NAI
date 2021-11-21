#include "lab_03.h"
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());


vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
{
    auto p = p0;

    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");

    //iterations of algorithm
    for (int i = 0; i < iterations; i++)
    {

        //candidate
        auto p2 = p;



        p2[distrib(gen)] += distrib_r(gen);

        if(!f_domain(p2))
        {
            //evaluate candidate point
            double y2 = f(p2);

            //check if keep new point
            if (y2 < f(p))
            {
                //store new point
                p = p2;
//            cout << p << " " << f(p) << endl;
            }
        }
        else
        {
            cout << "The current p2 point must be in domain" << endl;
        }





    }
    return p;
}


int sum (int a, int b) {

return a + b;
}

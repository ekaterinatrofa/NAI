#include "lab.h"
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <fstream>

using namespace std;

random_device rd;
mt19937 gen(rd());

std::string gnuplotrun()
{
    FILE* fp = popen("gnuplot script_hc.plt", "r");
    std::string stdout_plot = "";
    int ch = 0;
    while ((ch = fgetc(fp)) != EOF) {
        stdout_plot = stdout_plot + (char)ch;
    }
    int status = pclose(fp);
    if (status != 0) {
        throw std::invalid_argument("error generating chart");
    }

    return stdout_plot;
}

std::string gnuplotrun_1()
{
    FILE* fp = popen("gnuplot script_sa.plt", "r");
    std::string stdout_plot = "";
    int ch = 0;
    while ((ch = fgetc(fp)) != EOF) {
        stdout_plot = stdout_plot + (char)ch;
    }
    int status = pclose(fp);
    if (status != 0) {
        throw std::invalid_argument("error generating chart");
    }

    return stdout_plot;
}
/**

The hill climbing

**/

vector<double> hill_climbing(function<double(vector<double>)> f,
                             function<bool(vector<double>)> f_domain,
                             vector<double> p0, int iterations)
{
    auto p = p0;

    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");


     std::ofstream hcFile;
     hcFile.open("hc.txt");

    //iterations of algorithm
    for (int i = 0; i < iterations; i++)
    {

        //candidate
        auto p2 = p;

        p2[distrib(gen)] += distrib_r(gen);

        if(f_domain(p2))
        {
            //evaluate candidate point
            double y2 = f(p2);

            //check if keep new point
            if (y2 < f(p))
            {
                //store new point
                p = p2;


              cout<< i << p << " " << f(p) << endl;
                 hcFile <<  i<<  '\t';
                 hcFile <<f(p);
                 hcFile << '\n';


            }
        }
        else
        {
            cout << "The current p2 point must be in domain" << endl;
        }
    }
    hcFile.close();
    cout << gnuplotrun() << endl;
    return p;
}


/**

The simulated annealing

**/

vector<double> simulated_annealing(
               function<double(vector<double>)> f,             //goal function
               function<bool(vector<double>)> f_domain,
               vector<double> p0,
               int iterations,
               function<vector<double>(vector<double>)> N,
               function<double(int)> T                       //temperature
                                )
{
    auto s_current = p0;
    auto s_global_best = p0;

    uniform_real_distribution<> u_k(0.0, 1.0);

    if (!f_domain(s_current)) throw std::invalid_argument("The p0 point must be in domain");



    std::ofstream saFile;
     saFile.open("sa.txt");

    for (int k = 0; k < iterations; k++) {

        auto s_next = N(s_current);

        if (f_domain(s_next)){

        if (f(s_next) < f(s_current)) {

            s_current = s_next;

        }} else {

            double u = u_k(gen);

            if(f_domain(s_next)){

            if (u < exp(-abs(f(s_next) - f(s_current)) / T(k))) {

                s_current = s_next;

            } } else {
                // nothing...
            }
        }
        if (f(s_current) < f(s_global_best)) {
            s_global_best = s_current;
        }

    //   std::cout << s_current << " " << f(s_current) << endl;

                 saFile << k <<  '\t';
                 saFile <<f(s_current);
                 saFile << '\n';
    }

     saFile.close();
      cout << gnuplotrun_1() << endl;
    return s_global_best;
}

ostream& operator<<(ostream& o, vector<double> v)
{
    for (auto e : v)
    {
        o << std::fixed << std::setprecision(5) << " " << e;
    }
    return o;
}


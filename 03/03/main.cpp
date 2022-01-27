#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <functional>
#include <iomanip>
#include <map>
#include "lab.h"
using namespace std;



random_device rdn;  //Will be used to obtain a seed for the random number engine
mt19937 mt_generator(rdn()); //Standard mersenne_twister_engine seeded with rd()



/**
matyas function
**/

auto matyas = [](vector <double> v)

{
    double x = v.at(0), y = v.at(1);
    return 0.26 * (pow(x, 2) + pow(y, 2))- 0.48*x*y;
};

auto matyas_domain = [](vector <double> v)

{
    return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
};

/**

eggholder function
**/

auto eggholder_function = [](vector <double> v)
{

    double x = v.at(0), y = v.at(1);

    double kk = abs(x/2 + (y + 47));
    double ll = abs(x - (y + 47));

    return -(y + 47)*sin(sqrt(kk)) - x*sin(ll);

};

auto eggholder_function_domain = [](vector <double> v)
{
    return (abs(v[0]) <= 512) && (abs(v[1]) <= 512);
};

int main()
{

    int choice;
    do
    {
        cout << "Please select the function: "<< endl;
        cout << endl;
        cout << "1 -------> Matyas function " << endl;
        cout << "2 -------> Eggholder function" << endl;
        cout << "3 -------> Quit" << endl;
        cout << endl;
        cout << "Enter 1, 2 or 3: " << endl;

        auto foo_matyas = matyas;
        auto mat_dom = matyas_domain;

        auto foo_egg = eggholder_function;
        auto egg_dom = eggholder_function_domain;

        cin >>choice;


        while (choice < 1 || choice > 3)
        {
            cout << "Please enter a valid choice" << endl;

            cout << "Enter 1, 2 or 3: " << endl;

            cin >> choice;
        }

        switch(choice)
        {

        case 1:
        {
            cout << "You have selected Matyas function"<< endl;
            cout << endl;

            cout << "Please choose the algorithm: " << endl;

            cout << "1 -------> Hill Climbing " << endl;
            cout << "2 -------> Simulated annealing " << endl;
            cout << "3 -------> Compare Hill Climbing and Simulated annealing" << endl;

            int choice_1;
            cin >> choice_1;

            switch(choice_1)
            {

            case 1:
            {

                cout << "You have selected Hill Climbing" << endl;
                cout << endl;

                uniform_real_distribution<> distrib_r(-10, 10);

                //punkt początkowy losowany z dziedziny [-10;10]

                vector<double> matyas_p0 =
                {
                    distrib_r(mt_generator),
                    distrib_r(mt_generator),

                };

                int n;

                cout << "Please enter the number of iterations for function  " << endl;
                cin >> n;

                auto result_matyas = hill_climbing(foo_matyas, mat_dom, matyas_p0, n);

                cout << "f(" << result_matyas << ") = "<< " " << foo_matyas(result_matyas) << endl;
                cout << endl;

                break;

            }

            case 2:
            {

                cout << "You have selected Simulated annealing " << endl;
                cout << endl;

                uniform_real_distribution<> distrib_r(-10, 10);

                //punkt początkowy losowany z dziedziny [-10;10]

                vector<double> matyas_p0 =
                {
                    distrib_r(mt_generator),
                    distrib_r(mt_generator),

                };

                int n;

                cout << "Please enter the number of iterations for function  " << endl;
                cin >> n;
                auto result_matyas= simulated_annealing(foo_matyas, mat_dom, matyas_p0, n,
                                                        [](auto p)
                {
                    normal_distribution<double> n(0.0, 0.3);
                    for (auto& e : p)
                    {
                        e = e + n(mt_generator);
                    }
                    return p;
                },

                [](int k)
                {
                    return 1000.0 / k;
                });

                cout << "f(" << result_matyas << ") = "<< " " << foo_matyas(result_matyas) << endl;
                cout << endl;
                break;
            }

            case 3:
            {

                cout << "Comparing HC & SA" << endl;
                cout << "Provide the number of iterations for tests" << endl;
                int ni;

                cin >> ni;



                int hc_sa = 0;



                for (int i = 0; i < ni; i++)
                {


                    int itr = 1000;


                    auto f = matyas;

                    uniform_real_distribution<> distrib_r(-10, 10);



                    vector<double> matyas_p0 =
                    {
                        distrib_r(mt_generator),
                        distrib_r(mt_generator),

                    };
                    auto matyas_hc = hill_climbing(f, mat_dom, matyas_p0, itr);

                    auto matyas_sa= simulated_annealing(f, mat_dom, matyas_p0, itr,
                                                        [](auto p)
                    {
                        normal_distribution<double> n(0.0, 0.3);
                        for (auto& e : p)
                        {
                            e = e + n(mt_generator);
                        }
                        return p;
                    },

                    [](int k)
                    {
                        return 1000.0 / k;
                    });

                    cout << "Hill climbing:           ";
                    cout << " result = " << f(matyas_hc) << " " << endl;

                    cout << "simmulated annealing: ";
                    cout << " result = " << f(matyas_sa) << " " << endl;



                    if (f(matyas_hc) > f(matyas_sa))
                    {
                        hc_sa++;
                    }
                }

                cout << "Simmulated annealing was better " << hc_sa << " times " << "from " << ni << " iterations"<<endl;



                break;
            }

            }
            break;

        }

        case 2:
        {
            cout << "You have selected Eggholder function" << endl;
            cout << endl;

            cout << "Please choose the algorithm: " << endl;

            cout << "1 -------> Hill Climbing " << endl;
            cout << "2 -------> Simulated annealing " << endl;
            cout << "3 -------> Compare Hill Climbing and Simulated annealing" << endl;



            int choice_2;
            cin >> choice_2;

            switch(choice_2)
            {

            case 1:
            {

                cout << "You have selected Hill Climbing" << endl;
                cout << endl;

                uniform_real_distribution<> distrib_r(-512, 512);

                //punkt początkowy losowany z dziedziny [-512;512]

                vector<double> eggholder_function_p0 =
                {
                    distrib_r(mt_generator),
                    distrib_r(mt_generator),
                };

                int n;

                cout << "Please enter the number of iterations for function  " << endl;
                cin >> n;

                auto result_eggholder = hill_climbing(foo_egg, egg_dom, eggholder_function_p0, n);

                cout << "f(" << result_eggholder << ") = "<< " " << foo_egg(result_eggholder) << endl;
                cout << endl;

                break;

            }

            case 2:
            {

                cout << "You have selected Simulated annealing " << endl;
                cout << endl;

                uniform_real_distribution<> distrib_r(-512, 512);

                //punkt początkowy losowany z dziedziny [-512;512]

                vector<double> eggholder_function_p0 =
                {
                    distrib_r(mt_generator),
                    distrib_r(mt_generator),
                };


                int n;

                cout << "Please enter the number of iterations for function  " << endl;
                cin >> n;
                auto result_eggholder= simulated_annealing(foo_egg, egg_dom, eggholder_function_p0, n,
                                       [](auto p)
                {
                    normal_distribution<double> n(0.0, 0.3);
                    for (auto& e : p)
                    {
                        e = e + n(mt_generator);
                    }
                    return p;
                },

                [](int k)
                {
                    return 1000.0 / k;
                });

                cout << "f(" << result_eggholder << ") = "<< " " << foo_egg(result_eggholder) << endl;
                cout << endl;
                break;
            }


            case 3:
            {
                cout << "Comparing HC & SA" << endl;
                cout << "Provide the number of iterations for tests" << endl;
                int ni;

                cin >> ni;



                int hc_sa = 0;



                for (int i = 0; i < ni; i++)
                {


                    int itr = 100000;


                    auto f1 = eggholder_function;

                    uniform_real_distribution<> distrib_r(-512, 512);


                    vector<double> eggholder_function_p0 =
                    {
                        distrib_r(mt_generator),
                        distrib_r(mt_generator),
                    };
                    auto egg_hc = hill_climbing(f1, egg_dom, eggholder_function_p0, itr);

                    auto egg_sa= simulated_annealing(f1, egg_dom, eggholder_function_p0, itr,
                                                     [](auto p)
                    {
                        normal_distribution<double> n(0.0, 0.3);
                        for (auto& e : p)
                        {
                            e = e + n(mt_generator);
                        }
                        return p;
                    },

                    [](int k)
                    {
                        return 1000.0 / k;
                    });

                    cout << "Hill climbing:           ";
                    cout << " result = " << f1(egg_hc) << " " << endl;

                    cout << "simmulated annealing: ";
                    cout << " result = " << f1(egg_sa) << " " << endl;


                    if (f1(egg_hc) > f1(egg_sa))
                    {
                        hc_sa++;
                    }
                }

                cout << "Simmulated annealing was better " << hc_sa << " times " << "from " << ni << " iterations"<<endl;


                break;
            }



            break;

            }

            break;
        }

            case 3:
                cout << "Goodbye" << endl;
                cout << endl;
                break;
            }

        }
        while (choice <= 2 && choice >= 1);


        return 0;


    }




#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <functional>
#include <iomanip>

using namespace std;



random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

ostream& operator<<(ostream& o, vector<double> v)
{
    for (auto e : v)
    {
        o << std::fixed << std::setprecision(5) << " " << e;
    }
    return o;
}

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



int main()
{

    int choice;
    do
    {

        cout << "Please select the function: "<< endl;
        cout << endl;
        cout << "1 -------> Matyas function " << endl;
        cout << "2 -------> Schaffer function N. 2" << endl;
        cout << "3 -------> Eggholder function" << endl;
        cout << "4 -------> Quit" << endl;
        cout << endl;
        cout << "Enter 1, 2, 3, or 4: " << endl;

        cin >>choice;


        while (choice < 1 || choice > 4)
        {
            cout << "Please enter a valid choice" << endl;

            cout << "Enter 1, 2, 3, or 4: " << endl;

            cin >> choice;
        }

        switch(choice)
        {

        case 1:
        {
            cout << "You have selected Matyas function"<< endl;
            cout << endl;

            auto matyas = [](vector <double> v)

            {
                double x = v.at(0), y = v.at(1);
                return 0.26 * (pow(x, 2) + pow(y, 2))- 0.48*x*y;
            };

            auto matyas_domain = [](vector <double> v)
            {
                return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
            };


            uniform_real_distribution<> distrib_r(-10, 10);

            //punkt początkowy losowany z dziedziny [-10;10]

            vector<double> matyas_p0 =
            {
                distrib_r(gen),
                distrib_r(gen),
            };


            int n;

            cout << "Please enter the number of iterations for function  " << endl;

            cin >>n;

            auto result_matyas= hill_climbing(matyas, matyas_domain,matyas_p0, n);

            cout << "f(" << result_matyas << ") = "<< " " << matyas(result_matyas) << endl;
            cout << endl;
            break;
        }


        case 2:
        {
            cout << "You have selected Schaffer function N. 2" << endl;
            cout << endl;
            auto Schaffer_function_N_2 = [](vector <double> v)
            {

                double x = v.at(0), y = v.at(1);

                double xx = pow(x,2)-pow(y,2); // x^2 - y^2

                double sin_2 = 0.5*(1 - cos(2 * xx));
                double numerator = sin_2 - 0.5;

                double denominator = pow((1+0.001*(pow(x,2)+ pow(y,2)) ),2);
                return 0.5 + (numerator/denominator);

            };


            auto Schaffer_function_N_2_domain = [](vector <double> v)
            {
                return (abs(v[0]) <= 100) && (abs(v[1]) <= 100);
            };


            uniform_real_distribution<> distrib_r(-100, 100);

            //punkt początkowy losowany z dziedziny [-100;100]

            vector<double> Schaffer_function_N_2_p0 =
            {
                distrib_r(gen),
                distrib_r(gen),
            };

            int n;

            cout << "Please enter the number of iterations for function  " << endl;

            cin >>n;

            auto result_Schaffer_function_N_2= hill_climbing(Schaffer_function_N_2, Schaffer_function_N_2_domain,Schaffer_function_N_2_p0, n);

            cout << "f(" << result_Schaffer_function_N_2 << ") = "<< " " << Schaffer_function_N_2(result_Schaffer_function_N_2) << endl;
            cout << endl;
            break;

        }


        case 3:
        {
            cout << "You have selected Eggholder function" << endl;
            cout << endl;
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


            uniform_real_distribution<> distrib_r(-512, 512);

            //punkt początkowy losowany z dziedziny [-100;100]

            vector<double> eggholder_function_p0 =
            {
                distrib_r(gen),
                distrib_r(gen),
            };

            int n;

            cout << "Please enter the number of iterations for function  " << endl;

            cin >>n;

            auto result_eggholder_function= hill_climbing(eggholder_function, eggholder_function_domain,eggholder_function_p0, n);

            cout << "f(" << result_eggholder_function << ") = "<< " " << eggholder_function(result_eggholder_function) << endl;
            cout << endl;
            break;

        }

        case 4:
            cout << "Goodbye" << endl;
            cout << endl;
        }

    }
    while (choice <= 3 && choice >= 1);


    return 0;


}




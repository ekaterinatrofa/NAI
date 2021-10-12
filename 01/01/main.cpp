#include <iostream>
#include <math.h>

using std:: cout;
using std:: endl;


struct myStruct
{
    int xx;
    int yy;

};

auto foo1 = [](int x)
{
    return 20 - abs(x);
};


auto foo2 = [](int i)
{

    return  (2 * (i%2) - 1)*i/2;
};
auto foo3 = [](int x)
{

    return 2*x + 2;
};

auto foo4 = [](int x)
{

    return pow(x, 3);
};
auto obliczenia = [](auto f1, auto f2, int n)
{
    int max_x = f2(0);
    int max_y = f1(max_x);

    for (int i = 1; i < n; i++)
    {


        int x = f2(i);
        std::cout << "x = " << x << endl;

        int y = f1(x);
        cout << "y = " << y << endl;

        if (y > max_y)
        {

            max_x = x;
            max_y = y;
        }
        cout << "========="<<endl;
    }
    myStruct result;
    result.xx = max_x;
    result.yy = max_y;

    return result;


};

int main()
{

    myStruct calc = obliczenia(foo1, foo2, 5);

    cout << calc.xx << " : " << calc.yy <<endl;


    return 0;
}

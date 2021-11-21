#include <vector>
#include <random>
#include <functional>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <math.h>

#include "ga.hpp"

std::random_device r;
std::default_random_engine e1(r());



int main()
{

    auto eggholder = [](double x, double y)
    {
        return -(y+47.0)*sin(sqrt(std::abs((x/2.0)+(y+47.0))))-x*sin(sqrt(std::abs(x-(y+47.0))));
    };


    auto fitness = [](phenotype phen, auto func)
    {
        return 1.0 / (1.0 + abs(func(phen.x, phen.y)));
    };


    auto phen_generator = [](int size = 128)
    {

        std::uniform_int_distribution<int> uniform_dist(0,1);

        std::vector<int> result;

      //  std:: cout <<"Random generated : "<<std::endl;
        for (int i = 0; i < size; i++)
        {
            result.push_back(uniform_dist(e1));

        }

//        for (auto f : result)
//        {
//
//
//            std:: cout<< f;
//        }
      // std::cout <<std::endl;


        return result;
    };

    std::vector<phenotype> population; //creating population

    for (int i = 0; i < 20; i++)
    {
        phenotype tmp = convert_genotype_to_phenotype(phen_generator());

        convert_phenotype_to_genotype(tmp);

        tmp.fitness = fitness(tmp, eggholder);
        population.push_back(tmp);


    }



    for (auto specimen : population)
    {
        std::cout << "[ " << specimen.x << ", " << specimen.y << "] -> " << eggholder(specimen.x, specimen.y) << std::endl;
    }



}

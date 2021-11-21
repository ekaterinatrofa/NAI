#include <vector>
#include <cmath>
#include <iostream>
#include "ga.hpp"

using big_number = unsigned long long int;

std::vector<int> convert_phenotype_to_genotype(phenotype phen)
{

    std::vector<int> genotype;
    std::vector<int> binary(128);




    double max_val = (double)std::numeric_limits<uint64_t>::max();

    big_number x = (phen.x + 512)/1024 * max_val;
    big_number y = (phen.y + 512)/1024 * max_val;

//big_number x = ((phen.x / pow(10, 20)) + (0.185 / 2)) * (max_val * 10.85);
//    big_number y = ((phen.y / pow(10, 20)) + (0.185 / 2)) * (max_val * 10.85);

//std::cout << "nn " <<phen.x;
//std::cout <<std::endl;
    for(int i = 128 / 2; i > 0; i--)
    {
        binary.at(i - 1) = x % 2;


        x /= 2;

    }

    for(int i = 128; i > 128 / 2; i--)
    {
        binary.at(i - 1) = y % 2;
        y /=  2;
    }

    for(int i = 0; i < 128; i++)
    {
        genotype.push_back(binary.at(i));
     //  std::cout << binary.at(i);

    }

//    for(auto b : genotype) {
//
//        std:: cout << b;
//    }
// std::cout <<std::endl;
    return genotype;
}

phenotype convert_genotype_to_phenotype(std::vector<int> genotype)
{
    unsigned int const half = genotype.size() / 2;

    std::vector<int> phen_array_x(genotype.begin(), genotype.begin() + half);
    std::vector<int> phen_array_y(genotype.begin() + half, genotype.end());

    phenotype phen;

   // std::cout << "before x : ";

    /*for (auto ff : phen_array_x)
    {

        std::cout << ff;
    }
    std::cout <<std::endl;


     std::cout << "before y : ";

    for (auto ff : phen_array_y)
    {

        std::cout << ff;
    }*/
 //   std::cout <<std::endl;

    for (int i = phen_array_x.size() - 1; i >= 0; i--)
    {
        phen.x += phen_array_x.at(i) * pow(2, i);



    }


    for (int i = phen_array_y.size() - 1; i >= 0; i--)
    {
        phen.y += phen_array_y.at(i) * pow(2, i);
    }

    double max_val = (double)std::numeric_limits<uint64_t>::max();

    phen.x = -512+ phen.x/max_val*1024;
    phen.y = -512+ phen.y/max_val*1024;
// phen.x = (phen.x / pow(10, 20) - 0.185 / 2) * (max_val * 10.85);
//    phen.y = (phen.y / pow(10, 20) - 0.185 / 2) * (max_val* 10.85);
  //  std::cout << "x : " << phen.x << std:: endl;

    //std::cout << "y : " << phen.y << std:: endl;

    return phen;
}




#include <vector>
#include <cmath>
#include <iostream>
#include "ga.hpp"

using big_number = unsigned long long int;

std::vector<int> convert_phenotype_to_genotype(phenotype phen, double domain_max) {

    std::vector<int> genotype;
    std::vector<int> binary(128);

//    big_number x = ((phen.x / pow(10, 20)) + (0.185 / 2)) * (domain_max * 10.85);
//    big_number y = ((phen.y / pow(10, 20)) + (0.185 / 2)) * (domain_max * 10.85);


    double max_val = (double)std::numeric_limits<uint64_t>::max();

    big_number x =(uint64_t)((phen.x + 512)/1024 * max_val);
    big_number y = (uint64_t)((phen.y + 512)/1024 * max_val);



    for(int i = 128 / 2; i > 0; i--) {
        binary.at(i - 1) = x % 2;
        x /= 2;
    }

    for(int i = 128; i > 128 / 2; i--) {
        binary.at(i - 1) = y % 2;
        y /=  2;
    }

    for(int i = 0; i < 128; i++)
        genotype.push_back(binary.at(i));

    return genotype;
}

phenotype convert_genotype_to_phenotype(std::vector<int> genotype, double domain_max) {
    unsigned int const half = genotype.size() / 2;

    std::vector<int> phen_array_x(genotype.begin(), genotype.begin() + half);
    std::vector<int> phen_array_y(genotype.begin() + half, genotype.end());

    phenotype phen;
    for (int i = phen_array_x.size() - 1; i >= 0; i--) {
        phen.x += phen_array_x.at(i) * pow(2, i);
    }

    for (int i = phen_array_y.size() - 1; i >= 0; i--) {
        phen.y += phen_array_y.at(i) * pow(2, i);
    }

    /*
        We divide our values by 10^20 to reduce them to max 1.8 (because the maximum value we can use in C++ is 1.8 * 10^20).
        Next, we subtract half of the max value to allow use of negative numbers. At last, we multiply them to match their domain.
     */
    // std::cout << phen.x << " -> "<< phen.y << std::endl;
//    phen.x = (phen.x / pow(10, 20) - 0.185 / 2) * (domain_max * 10.85);
//    phen.y = (phen.y / pow(10, 20) - 0.185 / 2) * (domain_max * 10.85);

    double max_val = (double)std::numeric_limits<uint64_t>::max();

    phen.x = -512+ phen.x/max_val*1024;
    phen.y = -512+ phen.y/max_val*1024;
//std::cout << phen.x << " -> "<< phen.y << std::endl;
    phen.chromosome = genotype;
    return phen;
}

void phenotype::updatePhenotype(std::vector<int> chromosome, double domain_max) {
    phenotype buffer = convert_genotype_to_phenotype(chromosome, domain_max);
    this->x = buffer.x;
    this->y = buffer.y;
}

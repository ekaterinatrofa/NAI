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

auto printResults = [](std::vector<phenotype> results, auto func, auto fitness, std::string description) {
    std::cout << "============" << description << "============" << std::endl;
    for (auto result : results)
    {
        std::cout << "[ " << result.x << ", " << result.y << "] -> " << fitness(result, func) << std::endl;
    }
};
auto ga = [](
              auto generate_population,
              auto calculate_pop_fitness,
              auto term_condition,
              auto selection,
              auto crossover,
              auto mutation)

{
    auto population = generate_population();
    population = calculate_pop_fitness(population);

    while (!term_condition(population))
    {
        auto parents = selection(population);

        auto offspring = crossover(parents, 512);

        offspring = mutation(offspring);

        auto new_population = calculate_pop_fitness(offspring);

        std::sort(population.begin(), population.end(), [](auto a, auto b)
        {
            return a.fitness > b.fitness;
        });

        std::sort(new_population.begin(), new_population.end(), [](auto a, auto b)
        {
            return a.fitness > b.fitness;
        });

        //std::cerr << new_population.at(0).fitness  << " vs " << new_population.back().fitness  << std::endl;

        population = new_population;
    }
    return population;
};

///Roulette selection

auto selection_roulette = [](auto population)
{
    decltype(population) selected_phenotypes;

    double sum_fitness = accumulate(population.begin(), population.end(), 0.0, [](auto a, auto b)
    {
        return a + b.fitness;
    });

    std::uniform_real_distribution<double> uniform(0.0, sum_fitness);

    for (int c = 0; c < population.size(); c++)
    {
        double random_fit = uniform(e1);
        double sum_fit = 0.0;

        for (int i = 0; i < population.size(); i++)
        {
            sum_fit += population[i].fitness;
            if (random_fit < sum_fit)
            {
                selected_phenotypes.push_back(population.at(i));
                break;
            }
        }
    }
    return selected_phenotypes;
};

///Tournament selection

//auto selection_tournament = [](auto population, unsigned int tournament_size = 2)
//{
//    decltype(population) selected_phenotypes;
//    std::uniform_int_distribution<int> uniform(0, population.size()-1);
//
//     for (int c = 0; c < population.size(); c++)
//        {
//            decltype(population) tournament;
//            for (int t = 0; t < tournament_size; t++)
//            {
//                tournament.push_back(population.at(dist(rand_gen)));
//            }
//            sort(
//                tournament.begin(), tournament.end(), [](auto a, auto b) { return a.fit > b.fit; });
//            selected_specimens.push_back(tournament.at(0));
//        }
//        return selected_phenotypes;
//};

auto crossover_one_point = [](auto population, double domain_max, double p_crossover = 0.9)
{
    decltype(population) ret_pop;

    std::uniform_real_distribution<double> uniform_cross(0.0, 1.0);

    for (int i = 0; i < (population.size() - 1); i += 2)
    {
        auto a = population.at(i);
        auto b = population.at(i + 1);

        if (uniform_cross(e1) < p_crossover)
        {
            std::uniform_int_distribution<int> uniform(0, a.chromosome.size() - 1);
            auto crossover_p = uniform(e1);

            for (int g = crossover_p; g < a.chromosome.size(); g++)
            {
                std::swap(a.chromosome[g], b.chromosome[g]);
                a.updatePhenotype(a.chromosome, domain_max);
                b.updatePhenotype(b.chromosome, domain_max);
            }
        }
        ret_pop.push_back(a);
        ret_pop.push_back(b);
    }
    return ret_pop;
};


auto mutation_probabilitic = [](auto population, double p_mutation = 0.01)
{
    decltype(population) ret_pop;

    std::uniform_real_distribution<double> r_mut(0.0, 1.0);
    for (int i = 0; i < population.size(); i++)
    {
        auto a = population.at(i);//cur
        for (int j = 0; j < a.chromosome.size(); j++)
        {
            if (r_mut(e1) < p_mutation)
                a.chromosome[j] = 1 - a.chromosome[j];
        }
        a.updatePhenotype(a.chromosome,512);
        ret_pop.push_back(a);
    }
    return ret_pop;
};

auto get_term_condition = [](auto pop, int &iterations_max)
{
    auto term_condition = [&iterations_max](decltype(pop) population)
    {
        std::cout << "[" << iterations_max << "] ";

        double sum_fitness = accumulate(population.begin(), population.end(), 0.0, [](auto a, auto b)
        {
            return a + b.fitness;
        });

        std::cout << " { " << ((double)sum_fitness / (double)population.size()) << " } ";
        std::cout << std::endl;

        iterations_max--;
        if (iterations_max > 0)
            return false;
        else
            return true;
    };
    return term_condition;
};



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

//auto print_stats = [&fitness](auto comment, auto pop)
//{
//
//    auto best_of_all = *std::max_element(pop.begin(), pop.end(), [&](auto &a, auto &b)
//    {
//        return fitness(a) < fitness(b);
//    });
//
//    auto worse_of_all = *std::max_element(pop.begin(), pop.end(), [&](auto &a, auto &b)
//    {
//        return fitness(a) > fitness(b);
//    });
//
//    std::cout << "# [" << comment << "] best: " << fitness(best_of_all)  << std::endl;
//    std::cout << "# [" << comment << "] worse: " << fitness(worse_of_all) << std::endl;
//
//};
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

//    std::vector<phenotype> population; //creating population
//
//    for (int i = 0; i < 20; i++)
//    {
//        phenotype tmp = convert_genotype_to_phenotype(phen_generator());
//
//        convert_phenotype_to_genotype(tmp);
//
//        tmp.fitness = fitness(tmp, eggholder);
//        population.push_back(tmp);
//
//
//    }

    auto generate_population = [&phen_generator, &fitness, &eggholder]()
    {
        std::vector<phenotype> population;

        for (int i = 0; i < 100; i++)
        {
            phenotype tmp = convert_genotype_to_phenotype(phen_generator(),512);
            population.push_back(tmp);
        }
        return population;
    };

    auto calculate_fitness = [&fitness, &eggholder](const std::vector<phenotype> population)
    {
        std::vector<phenotype> results;
        results.reserve(population.size());
        for (auto phen : population)
        {
            phen.fitness = fitness(phen, eggholder);
            results.push_back(phen);
        }

        return results;
    };


    int iterations = 10;
    auto ga_results = ga(generate_population, calculate_fitness,  get_term_condition(std::vector<phenotype>(), iterations), selection_roulette, crossover_one_point, mutation_probabilitic);

    for (auto result : ga_results)
    {
        std::cout << "[ " << result.x << ", " << result.y << " ] --> " << fitness(result, eggholder) << "   "<< eggholder(result.x, result.y)<< std::endl;
    }





}

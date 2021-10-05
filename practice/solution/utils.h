#ifndef UTILS_H
#define UTILS_H 

#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "pizza_delivery.h" 

PizzaDelivery parse_input(const std::string& filename) 
{
    std::ifstream ifs(filename); 

    if (!ifs.is_open()) 
    {
    	throw std::ios_base::failure("Cannot open input file");
    }

    int numPizza, numTeamTwo, numTeamThree, numTeamFour;
    ifs >> numPizza >> numTeamTwo >> numTeamThree >> numTeamFour;

    // for debugging, print info 
    // std::cout << "numPizza " << numPizza << " numTeamTwo " << numTeamTwo << " numTeamThree " << numTeamThree << " numTeamFour " << numTeamFour << std::endl; 

    std::vector<int> teamNums = {numTeamTwo, numTeamThree, numTeamFour};     

    pizza_vec pizzas; 
    for (int i = 0; i < numPizza; ++i)
    {
	// read one pizza 
        pizza piz;  
	piz.index = i; 

        int numIngredients;
        std::string temp; 
        ifs >> temp;
	numIngredients = std::stoi(temp);
        piz.numIngredients = numIngredients;	

        // for debugging
	// std::cout << "numIngredients: " << numIngredients << std::endl; 

	for (int j = 0; j < numIngredients; ++j) 
	{
	    std::string ingredient;
 	    ifs >> ingredient;
            piz.ingredients.push_back(ingredient);
	}
        
	// sort the ingredients, maybe useless	
        // std::sort(piz.ingredients.begin(), piz.ingredients.end());
	
	pizzas.push_back(piz);
    }
    
    // for debugging, print input pizza info 
    // std::cout << pizzas;
	
    return PizzaDelivery(pizzas, teamNums); 
}

void save_results(std::unordered_multimap<int, std::vector<int>>& results, const std::string& filename)
{
    std::ofstream ofs(filename); 

    if (!ofs.is_open()) 
    {
        throw std::ios_base::failure("Cannot open the output file");
    }

    // write the number of teams 
    ofs << results.size() << std::endl; 

    std::unordered_map<int, std::vector<int>>::iterator it = results.begin();
    while (it != results.end())
    {
        ofs << it->first << " ";
	for (const auto& piz_id : it->second)
	    ofs << piz_id << " "; 
	ofs << "\n"; 

	it++; 
    }

    ofs.close();

}

#endif // UTILS_H 

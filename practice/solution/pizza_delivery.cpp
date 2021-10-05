#include "pizza_delivery.h"

#include <iostream> 
#include <numeric> 

std::ostream& operator<<(std::ostream& os, pizza_vec pv) noexcept
{
    for (const auto& pizza : pv)
    {
	os << "pizza index: " << pizza.index << " number of ingredients: " << pizza.numIngredients << std::endl; 
	os << "ingredients:" << std::endl; 
	for (const auto& ing : pizza.ingredients)
	{
	    os << ing << std::endl;  
	}
    }
    return os; 
}

std::unordered_multimap<int, std::vector<int>> PizzaDelivery::solve() noexcept
{
    std::unordered_multimap<int, std::vector<int>> results; 

    // while loop as long as team not zero and pizza not zero  
    // break when number of pizza available is smaller than existing smaller team size

    // select largest team whose size is smaller than number 
    // of remaining pizza 
    // select one pizza, and then select from remaining pizza which has min. overlap 
    // until all people in team gets one pizza  

    while (m_pizzas.size() && std::accumulate(m_teamNums.begin(), m_teamNums.end(), decltype(m_teamNums)::value_type(0)))
    {

	// break 
	int smallestTeamSize = 0; 	
	for (const auto& num : m_teamNums)
	{
	    if (num != 0) 
	    {
		smallestTeamSize = num; 
		break; 
	    }
	}
	if (m_pizzas.size() < smallestTeamSize)
	    break;  
        
	// select the largest team 	
	int largestTeamSize = 0; 
        int teamSize = 4; 
	for (auto it = m_teamNums.rbegin(); it != m_teamNums.rend(); ++it)
	{
	    if (*it != 0)
	    {
		largestTeamSize = teamSize; 
		*it = *it - 1; 
		break; 
	    }

	    teamSize--; 
	}
	
	// for debugging 
	// std::cout << "chosen team size: " << largestTeamSize << std::endl; 

	// for debuggging 
	// std::cout << "pizza size " << m_pizzas.size() << std::endl;     

	// check if we still have enough pizza 
	if (m_pizzas.size() < largestTeamSize)
	    continue; 

	std::vector<int> pizList; 
	
	// pick the pizza that has most new ingredients 
	std::vector<std::string> currentIngredList;	
	int tempTeamSize = largestTeamSize; 
 	while (tempTeamSize != 0)
	{
	    int largestNewIngred = 0; 
	    int chosenPizIndex; 
	    std::vector<std::string> newIngreds; 	
	    for (const auto& piz : m_pizzas)
	    {
		int numNewIngred = diff_ingred_for_cur_piz(currentIngredList, piz);
		if (largestNewIngred <= numNewIngred)
		{
		    largestNewIngred = numNewIngred; 
		    chosenPizIndex = piz.index; 
		    newIngreds = piz.ingredients; 
		}
	    }

	    // add new ingredients to the list 
	    for (const auto& ing : newIngreds)
	    {
	        if (std::find(currentIngredList.begin(), currentIngredList.end(), ing) == currentIngredList.end())
		    currentIngredList.push_back(ing); 
	    }
	    
	    // add chosen pizza to results 
	    pizList.push_back(chosenPizIndex);

	    // remove chosen pizza 
	    pizza_vec::iterator it = remove_if(m_pizzas.begin(), m_pizzas.end(), [chosenPizIndex](pizza piz){return piz.index == chosenPizIndex;}); 
	    m_pizzas.erase(it); 
	    
	    // decrease team size 
	    tempTeamSize--; 
	}	


	// write this team size in results 
 	results.emplace(largestTeamSize, pizList);
	    
    }

    return results; 
}	

int PizzaDelivery::diff_ingred_for_cur_piz(const std::vector<std::string>& ingList, const pizza& p) noexcept
{
    std::vector<std::string> v_temp; 
    
    std::set_intersection(ingList.begin(), ingList.end(),
			p.ingredients.begin(), p.ingredients.end(),
			std::back_inserter(v_temp));

    int numDiffIngred = p.numIngredients - v_temp.size();

    return numDiffIngred; 
}



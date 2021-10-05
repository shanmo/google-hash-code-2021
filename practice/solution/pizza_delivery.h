#ifndef PIZZA_DELIVERY_H
#define PIZZA_DELIVERY_H

#include <string> 
#include <unordered_map>
#include <vector>

struct pizza
{
    int index;
    int numIngredients; 
    std::vector<std::string> ingredients; 
}; 

using pizza_vec = std::vector<pizza>; 

std::ostream& operator<<(std::ostream& os, pizza_vec pv) noexcept;

class PizzaDelivery
{
public:
    // constructor 
    // default constructor 
    PizzaDelivery() = default;
    // default destructor 
    ~PizzaDelivery() = default; 
    
    // constructor we use 
    PizzaDelivery(const pizza_vec& pizzas, std::vector<int> teamNums) noexcept 
	: m_pizzas{pizzas}, m_teamNums{teamNums}
        {}

    // function to solve the problem 
    std::unordered_multimap<int, std::vector<int>> solve() noexcept; 

private:

    int diff_ingred_for_cur_piz(const std::vector<std::string>& ing_list, const pizza& p) noexcept;

    pizza_vec m_pizzas; 
    std::vector<int> m_teamNums; 
};

#endif //PIZZA_DELIVERY_H 

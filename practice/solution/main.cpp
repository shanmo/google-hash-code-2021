#include <exception>
#include <fstream>
#include <iostream>
#include <vector> 

#include "pizza_delivery.h"
#include "utils.h"

int main(int argc, const char* argv[]) 
{
    if (argc != 3)
    {
        std::cout << "Usage: pizza_hut <input_filename> <output_filename>\n";
    }

    // for debugging 
    // std::cout << "input " << argv[1] << std::endl; 
    // std::cout << "output " << argv[2] << std::endl; 

    try
    {
        PizzaDelivery pd = parse_input(argv[1]);
    	auto results = pd.solve();
	save_results(results, argv[2]); 
    }
    catch(const std::ios_base::failure& ios_exc) 
    {
        std::cout << ios_exc.what() << std::endl; 
        return 1;
    }

    return 0; 
}

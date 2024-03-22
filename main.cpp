#include <iostream>
#include <string>
#include "gradientMethod.hpp"


using Vector=std::vector<double>;


int main () {

    //asking the user to choose between the exact gradient and the finite differences gradient
    std::cout << "\n\nType  exact   if you want to use the exact gradient for the resolution,\notherwise type   finite    if you prefer to employ finite differences" << std::endl;
    std::string gradient_choice;
    std::cin >> gradient_choice;

    //xk will be updated with the point of minimum of the function
    Vector xk={};

    // call gradient method
    if(gradient_choice=="exact")
        gradient_method_exact(xk);
    else if(gradient_choice=="finite")
        gradient_method_finite(xk);

    return 0;
}
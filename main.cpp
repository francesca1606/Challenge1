#include <iostream>
#include <string>
#include "gradientMethod.hpp"


using Vector=std::vector<double>;


//Vector gradFiniteDiff(muParserXFun f, const Vector &x,  const double epsilon=1e-6);  //CAMBIA EPSILON!!!!!

int main () {

    //asking the user to choose between the exact gradient and the finite differences gradient
    std::cout << "\n\nType  exact   if you want to use the exact gradient for the resolution,\notherwise type   finite    if you prefer to employ finite differences" << std::endl;
    std::string gradient_choice;
    std::cin >> gradient_choice;

    Vector xk={};

    // call gradient method
    if(gradient_choice=="exact"){
        gradient_method_exact(xk);
    }
    else if(gradient_choice=="finite"){
             gradient_method_finite(xk);
    }
     
    return 0;
}
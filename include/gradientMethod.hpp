//This file contains the two main functions of this program, gradient_method_exact and gradient_method_finite
//The two functions rely on methods implemented in auxFunctions.hpp

#ifndef HH_GRADIENTMETHOD_HH
#define HH_GRADIENTMETHOD_HH

#include <vector>
#include <string>
#include "muParserFun.hpp"
#include "parameters.hpp"
#include "auxFunctions.hpp"

using Vector= std::vector<double>;


//Gradient method for computing the minimum of a function using the exact gradient contained in data.json
void gradient_method_exact(Vector & xk) {
    
    //create the struct for the parameters and read them from data.json
    params_for_GD g;
    read_parameters(g);
    
    xk.resize(g.dim);
    xk=g.x0;
    Vector xk1(g.dim);
    double alphak= g.alpha0;
    int k=0;
    bool break_cicle=false;
    double residual_norm=0.;

    //strategy to calculate the step at each iteration 
    constexpr strategies strat=strategies::inverse_decay; 
    constexpr type_of_grad T=type_of_grad::exact;


    muParserFun fun(g.dim,g.f_string);  
    //otherwise parser doesn't seem to read well the variables
    fun = muParserFun(g.dim,fun.getExpression());

    std::vector<muParserFun> dfun;   
    for (int i=0; i< g.dim; ++i){
       dfun.emplace_back(g.dim,g.df_string[i] );  
    }
    //otherwise parser doesn't seem to read well the variables
    for(auto & f:dfun)
        f = muParserFun(g.dim,f.getExpression());
  

    while(k<=g.max_iter && !break_cicle){

        //compute step for iteration k
        alphak = compute_step <strat, T>(g.alpha0,k, xk, g, fun); 

        //update xk1
        for (unsigned int i=0; i<xk.size(); ++i){
              xk1[i]= xk[i] - alphak*dfun[i](xk);      
        }
        
        //calculate gradient of xk1 for the arrest criteria
        Vector gradk1(g.dim);
        for (unsigned int i=0; i<xk.size(); ++i){
              gradk1[i]=dfun[i](xk1);
        }
        
        //stop criterias
        Vector difference= xk1 - xk;
        residual_norm= norm(gradk1);
        if(  norm(difference) < g.tol_x || residual_norm < g.tol_res)  {
             break_cicle=true;
        } 

        xk=xk1;
        k++;
    }

    //if the maximum number of iterations is reached, there's no convergence
    if( !break_cicle ){
        std::cout << "The method didn't converge in " << g.max_iter << " iterations\n";
        return;
    }

    std::cout << "\nNumber of iterations: " << k-1 << std::endl;
    std::cout << "Point of minimum: ";
    print(xk);
    std::cout << "Minimum value: " << fun(xk) << std::endl;
    std::cout << "Residual: " << residual_norm << std::endl;
    std::cout << "\n";
    
};


//Gradient method for computing the minimum of a function using the gradient computed through centered finite differences
void gradient_method_finite(Vector &xk){
        
    //create the struct for the parameters and read them from data.json
    params_for_GD g;
    read_parameters(g);

    xk.resize(g.dim);
    xk=g.x0;
    Vector xk1(g.dim);
    double alphak= g.alpha0;
    int k=0;
    bool break_cicle=false;
    double residual_norm=0.;
    
    //strategy to calculate the step at each iteration
    constexpr strategies strat=strategies::inverse_decay;
    constexpr type_of_grad T= type_of_grad::finite_grad;


    muParserFun fun(g.dim,g.f_string);  
    //otherwise parser doesn't seem to read well the variables
    fun=muParserFun(g.dim,fun.getExpression());


    while(k<=g.max_iter && !break_cicle){
    
        //compute step for iteration k
        alphak = compute_step <strat, T>(g.alpha0,k, xk, g, fun ); 

        //update xk1
        xk1=xk -alphak*gradFiniteDiff(fun, xk, g.epsilon);
        
        //calculate gradient of xk1 for the arrest criteria
        Vector gradk1=gradFiniteDiff(fun,xk1, g.epsilon);                //-gradFiniteDiff(fun,xk)[i];

        //stop criterias
        Vector difference= xk1 - xk;
        residual_norm= norm(gradk1);
        if(  norm(difference) < g.tol_x || residual_norm < g.tol_res)  {
             break_cicle=true;
        } 

        xk=xk1;
        k++; 
        
    }

    //if the maximum number of iterations is reached, there's no convergence
    if( !break_cicle ){
        std::cout << "The method didn't converge in " << g.max_iter << " iterations\n";
        return;
    }
    
    std::cout << "\nNumber of iterations: " << k-1 << std::endl;
    std::cout << "Point of minimum: ";
    print(xk);
    std::cout << "Minimum value: " << fun(xk) << std::endl;
    std::cout << "Residual: " << residual_norm << std::endl;
    std::cout << "\n";

}


#endif // HH_GRADIENTMETHOD_HH
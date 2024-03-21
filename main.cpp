#include <iostream>
#include <string>
#include "muParserXFun.hpp"
#include "parameters.hpp"
#include "auxFunctions.hpp"


using Vector=std::vector<double>;

//returns the minimum point of a given function
void gradient_method(Vector &xk);   
Vector gradFiniteDiff(muParserXFun &f,  Vector &x,  const double epsilon=1e-6);

int main () {


    // call gradient method
    Vector xk={};
    gradient_method(xk);
    std::cout << "fine" << std::endl;

     
    return 0;
};


void gradient_method(Vector & xk) {
    
    //create the struct for the parameters and read them from data.json
    params_for_GD g;
    read_parameters(g);
    
    xk.resize(g.dim);
    xk=g.x0;
    Vector xk1=xk;
    double alphak= g.alpha0;
    int k;
    double residual_norm=0.;

    constexpr strategies strat=strategies::exponential_decay; 

    muParserXFun fun(g.dim,g.f_string);  

    std::vector<muParserXFun> dfun;   
    for (int i=0; i< g.dim; ++i){
       dfun.emplace_back(g.dim,g.df_string[i] );  
    }

    //asking the user to choose between the exact gradient and the finite differences gradient
    std::cout << "\n\nType  exact   if you want to use the exact gradient for the resolution,\notherwise type   finite    if you prefer to employ finite differences" << std::endl;
    
    std::string gradient_choice;
    std::cin >> gradient_choice;
  
    for(k=0 ; k<=g.max_iter; ++k){
        alphak = compute_step <strat>(g.alpha0,k, xk, g, fun); 

        Vector gradk1(g.dim);
        
        if (gradient_choice=="exact"){   //not efficient to evaluate it every time !!!!!!!!!!!!!
          for (unsigned int i=0; i<xk.size(); ++i){
              xk1[i]= xk[i] - alphak*dfun[i](xk);      
          }
          std::cout << "Calcolo:  " << dfun[0]({-2,0}) <<" Con function: " << dfun[0].getExpression() << std::endl;
          //std::cout << "first component" << gradk1[0] ;
          //std::cout << "second component" << gradk1[1];
          //print(xk1);
          //print(xk)  ;
          //print(gradk1);

        }
        else{
              //user may add a different value of epsilon in the function call, default is 1e-6
              xk1= xk -  alphak* gradFiniteDiff(fun, xk);   
              gradk1= gradFiniteDiff(fun,xk1);
        }


        for (unsigned int i=0; i<xk.size(); ++i){
              gradk1[i]=dfun[i](xk1);
              gradk1[i]=dfun[i](xk1);
          }
        
        std::cout << "At iteration: " << k << " xk = " << xk[0] << " " << xk[1] << " xk1 = " << xk1[0] << " " << xk1[1] << std::endl;

        Vector difference= xk1 -xk;
        residual_norm= norm(gradk1);
        std::cout << "Vector grad : ";
        print(gradk1);
        std::cout << residual_norm<<std::endl;

        xk=xk1;
        //stop criteria
        if(  norm(difference) < g.tol_x || residual_norm < g.tol_res)  {
           //std::cout << norm(difference) << std::endl;
           break;
        } 
       
    }

    std::cout << "\nNumber of iterations: " << k << std::endl;
    std::cout << "Point of minimum: ";
    print(xk);
    std::cout << "Minimum value: " << fun(xk) << std::endl;
    std::cout << "Residual: " << residual_norm << std::endl;
    std::cout << "\n";
    
    return;
};


//computing the gradient of the function f given using finite differences
//method evaluates the gradient in a Vector x
Vector gradFiniteDiff ( muParserXFun &f,  Vector &x,  const double epsilon)
{
    int n= x.size();
    Vector grad(n,0.0);    
    
    //using a centered scheme to compute each partial derivative 
    for(int i=0; i<n ; ++i){
        Vector x_plus=x;
        x_plus[i] += epsilon;
        Vector x_minus=x;
        x_minus[i] -= epsilon;
        grad[i]= (f(x_plus) - f(x_minus))/(2*epsilon);
    }

    return grad;
}

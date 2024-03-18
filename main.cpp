#include <iostream>
#include <string>
#include "muParserXFun.hpp"
#include "parameters.hpp"
#include "auxFunctions.hpp"


using Vector=std::vector<double>;

//returns the minimum point of a given function
Vector gradient_method();   
Vector gradFiniteDiff(muParserXFun &f, const Vector &x,  const double epsilon=1e-6);

int main () {

    // call gradient method
    Vector minimumPt= gradient_method();
     
    return 0;
}


Vector gradient_method() {
    
    //create the struct for the parameters and read them from data.json
    params_for_GD g;
    read_parameters(g);

    Vector xk(g.x0), xk1(g.x0);
    double alphak= g.alpha0;
    int k=0;
    double residual_norm=0.;

    constexpr strategies strat=strategies::exponential_decay; 

    //asking the user to choose between the exact gradient and the finite differences gradient
    std::cout << "\nType  exact   if you want to use the exact gradient for the resolution,\notherwise type   finite differences    if you prefer to employ this" << std::endl;
    std::string gradient_choice;
    std::cin >> gradient_choice;
    

    for( ; k<=g.max_iter; ++k){
        alphak =  compute_step <strat>(alphak,k, xk, g); 

        Vector norm_gradk(xk.size()), norm_gradk1(xk.size());
        if (gradient_choice=="exact"){   //not efficient to evaluate it every time !!!!!!!!!!!!!
          for (int i=0; i<xk.size(); ++i){
            {           
              xk1[i]= xk[i] - alphak*g.dfun[i].evaluate(xk);
              norm_gradk[i]= g.dfun[i].evaluate(xk);
              norm_gradk1[i]= g.dfun[i].evaluate(xk);
            }
          }   
        }
        else{
              //user may add a different value of epsilon in the function call, default is 1e-6
              norm_gradk= gradFiniteDiff(g.fun, xk);
              xk1= xk -  alphak* gradFiniteDiff(g.fun, xk);      
              norm_gradk1= gradFiniteDiff(g.fun, xk1);
        }
        
        residual_norm= norm(norm_gradk1 - norm_gradk);

        //stop criteria
        if( norm(xk1 - xk)< g.tol_x ||  residual_norm < g.tol_res)   
            break;

        xk=xk1;
    }

    std::cout << "Number of iterations: " << k << std::endl;
    std::cout << "Point of minimum: ";
    print(xk1);
    std::cout << "Residual: " << residual_norm;
    
    return xk1;
}


//computing the gradient of the function f given using finite differences
//method evaluates the gradient in a Vector x
Vector gradFiniteDiff ( muParserXFun &f, const Vector &x,  const double epsilon)
{
    int n= x.size();
    Vector grad(n);    
    
    //using a centered scheme to compute each partial derivative 
    for(int i=0; i<n ; ++i){
        Vector x_plus=x;
        x_plus[i] += epsilon;
        Vector x_minus=x;
        x_minus[i] -= epsilon;
        grad[i]= (f.evaluate(x_plus) - f.evaluate(x_minus))/(2*epsilon);
    }

    return grad;
}

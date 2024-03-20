#include <iostream>
#include <string>
#include "muParserXFun.hpp"
#include "parameters.hpp"
#include "auxFunctions.hpp"


using Vector=std::vector<double>;

//returns the minimum point of a given function
void gradient_method(Vector &xk);   
Vector gradFiniteDiff(muParserXFun &f, const Vector &x,  const double epsilon=1e-6);

int main () {

try{
    Vector v({1,2});
    std::string f_s="x1+2*x2 + x1*x2";
    muParserXFun f(2,f_s);
    std::cout << f.evaluate(v) << std::endl;
}catch(const mup::ParserError& e) {
    std::cerr << "Parser error: " << e.GetMsg() << std::endl;
    // Handle the error, e.g., by logging it, displaying a message to the user, or exiting the program
}


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

    std::cout << g.f_string;
    muParserXFun fun(g.dim,g.f_string); 
    std::vector<muParserXFun> dfun;   
    for (int i=0; i< g.dim; ++i){
       dfun.emplace_back(g.dim,g.df_string[i]);
    }

    //asking the user to choose between the exact gradient and the finite differences gradient
    std::cout << "\nType  exact   if you want to use the exact gradient for the resolution,\notherwise type   finite differences    if you prefer to employ this" << std::endl;
    
    std::string gradient_choice;
    std::cin >> gradient_choice;

    for(k=0 ; k<=g.max_iter; ++k){
        std::cout << k << std::endl;
       
        alphak =  compute_step <strat>(alphak,k, xk, g, fun, dfun); 

        Vector norm_gradk(xk.size()), norm_gradk1(xk.size());
        
        if (gradient_choice=="exact"){   //not efficient to evaluate it every time !!!!!!!!!!!!!
          for (int i=0; i<xk.size(); ++i){
            {    
              print(xk);       
              xk1[i]= xk[i] - alphak*dfun[i].evaluate(xk);      
              norm_gradk[i]= dfun[i].evaluate(xk);
              norm_gradk1[i]= dfun[i].evaluate(xk);
            }
          }   
        }
        else{
              //user may add a different value of epsilon in the function call, default is 1e-6
              norm_gradk= gradFiniteDiff(fun, xk);
              xk1= xk -  alphak* gradFiniteDiff(fun, xk);   
              norm_gradk1= gradFiniteDiff(fun, xk1);
        }
        
        residual_norm= norm(norm_gradk1 - norm_gradk);

        //stop criteria
        if( norm(xk1 - xk)< g.tol_x ||  residual_norm < g.tol_res)   
            break;
        xk=xk1;
    }

    std::cout << "\nNumber of iterations: " << k-1 << std::endl;
    std::cout << "Point of minimum: ";
    print(xk);
    std::cout << "Minimum: " << fun.evaluate(xk) << std::endl;
    std::cout << "Residual: " << residual_norm << std::endl;
    
    return;
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

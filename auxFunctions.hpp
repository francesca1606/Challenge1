//Useful functions needed to implement the gradient descent method

#ifndef HH_AUXFUNCTIONS_HH
#define HH_AUXFUNCTIONS_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "json.hpp"
#include "muParserXFun.hpp"
#include "parameters.hpp"

using Vector=std::vector<double>;
using json = nlohmann::json;


//calculates the norm of a Vector object
double norm (const Vector &v) {
    double res=0.;
    for(auto &i: v ){
        res += i*i;
    }
    return std::sqrt(res);
};

//prints the elements of Vector on the row
void print(const Vector &v) {
    for( auto &i: v)
       std::cout << i << " ";
    std::cout << "\n";
};

//overloading of - operator
//if the sizes of the two vectors don't coincide, the function returns the first vector passed
Vector operator-(const Vector &v1, const Vector &v2){
    Vector result(v1.size());
    if(v1.size()==v2.size())
      for(unsigned int i=0; i<v1.size(); ++i)
          result[i]= v1[i] - v2[i];
    return result;
};

//product of a Vector with a double
//double*Vector
Vector operator*(double alpha, const Vector &v) {
      Vector result=v;
      for(auto &i: result)
          i = i * alpha;
      return result;
};




//computing the gradient of the function f given using finite differences
//method evaluates the gradient in a Vector x
Vector gradFiniteDiff ( muParserXFun f, const Vector &x, const double epsilon=1e-6)
{  
    int n= x.size();
    Vector grad(n,0.0);    
    f=muParserXFun(n,f.getExpression());

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


//Strategies to calculate step alphak at each iteration

enum strategies{
    exponential_decay, inverse_decay, Armijo_rule
};

enum type_of_grad{
    exact, finite_grad
};

double exp_decay(const int k,const double alpha0, const double mu) {
    return alpha0*std::exp(-mu*k);
};

double inv_decay(const int k, const double alpha0, const double mu) {
    return alpha0/(1+ mu*k);
};

double line_search_exact(const double alpha0, const Vector& xk, const double sigma, const int Armijo_iter, muParserXFun &f, std::vector<std::string> df_string){   
    if(sigma>0 && sigma<0.5){

        int n=xk.size();
        bool break_cicle=false;
        double alphak= alpha0;
        int k=0;

        //otherwise parser doesn't seem to read well the variables
        f=muParserXFun(n, f.getExpression());
    
        std::vector<muParserXFun> df;

        
        for(auto & s: df_string)
            df.push_back(muParserXFun(n, s));
        //otherwise parser doesn't seem to read well the variables
        for(auto & d: df)
            d= muParserXFun(n, d.getExpression());
        
        Vector long_expr(n), gradk(n);

        while(k < Armijo_iter && !break_cicle){
            
            for(int i=0; i<n; ++i){
                long_expr[i]= xk[i] - alphak*df[i](xk); 
                gradk[i]= df[i](xk);
            }
        
            //Armijo rule
            if (f(xk) - f(long_expr) >= sigma*alpha0*norm(gradk)*norm(gradk) )
                break_cicle=true;
            else
                alphak= alphak/2;
        }

        return alphak;
    }

    std::cerr<< "Sigma has to be in the interval (0, 0.5)" << std::endl;
    return alpha0 ;
};

double line_search_finite(const double alpha0, const Vector& xk, const double sigma, const int Armijo_iter, muParserXFun &f){
    if(sigma>0 && sigma<0.5){

        int n=xk.size();
        bool break_cicle=false;
        double alphak= alpha0;
        int k=0;

        //otherwise parser doesn't seem to read well the variables
        f=muParserXFun(n, f.getExpression());
    
        Vector long_expr(n), gradk(n);
        
        while(k < Armijo_iter && !break_cicle){
            
            gradk=gradFiniteDiff(f,xk);
            long_expr= xk - alphak*gradFiniteDiff(f, xk);
            
            //Armijo rule
            if (f(xk) - f(long_expr) >= sigma*alpha0*norm(gradk)*norm(gradk) )
                break_cicle=true;
            else
                    alphak= alphak/2;
        }

        return alphak;
    }

    std::cerr<< "Sigma has to be in the interval (0, 0.5)" << std::endl;
    return alpha0 ;
};

template<strategies S, type_of_grad T>
double compute_step(const double alpha0, const int k, const Vector &xk, params_for_GD &g, muParserXFun & f)  {
    if constexpr(S==strategies::exponential_decay)
       return exp_decay(k, alpha0, g.mu);
    if constexpr(S==strategies::inverse_decay)
       return inv_decay(k, alpha0, g.mu);
    if constexpr(T==type_of_grad::exact)
       return line_search_exact(alpha0, xk, g.sigma, g.Armijo_iter, f, g.df_string);
    return line_search_finite(alpha0, xk, g.sigma, g.Armijo_iter, f);
};


#endif // HH_AUXFUNCTIONS_HH

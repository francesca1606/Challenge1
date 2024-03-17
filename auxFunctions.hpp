//Useful functions needed to implement the gradient descent method

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "json.hpp"
#include "muParserXFun.hpp"
#include "parameters.hpp"



using Vector=std::vector<double>;
using json = nlohmann::json;


//calculates the norm of a Vector object
double norm (const Vector v) {
    double res=0;
    for(auto &i: v ){
        res += i*i;
    }
    return std::sqrt(res);
}

//prints the elements of Vector on the row
void print(const Vector &v) {
    for( auto &i: v)
       std::cout << i << " ";
    std::cout << "\n";
}



//Strategies to calculate step alphak at each iteration

enum strategies{
    exp_decay, inv_decay, line_search
};

double exp_decay(const int k,const double alpha, const double mu) {
    return alpha*exp(-mu*k);
}
double inv_decay(const int k, const double alpha, const double mu) {
    return alpha/(1+ mu*k);
}
double line_search(const double alpha, const Vector& xk, const double sigma, muParserXFun f, std::vector<muParserXFun> df)  {   //serve qualcosa per leggere funzione
    if(sigma>0 || sigma<0.5){
        Vector s(xk.size()), normk=s;
        
        for (int i=0; i<xk.size(); ++i){
            normk[i]= df[i].evaluate(xk);
            s[i]=  xk[i] - alpha*normk[i];
        }
        
        if ( f.evaluate(xk) - f.evaluate(s) >= sigma*alpha*norm(normk)*norm(normk) )
          return alpha;
        else
            return line_search(alpha/2, xk, sigma, f, df);
    }
    std::cerr<< "Sigma has to be in the interval (0, 0.5)" << std::endl;
    return -1. ;
}

template<strategies S>
double compute_step(const double alphak, const int k, const Vector &xk, const params_for_GD &g)  {
    if constexpr(S==strategies::exp_decay)
       return exp_decay(k, alphak, g.mu);
    if constexpr(S==strategies::inv_decay)
       return inv_decay(k, alphak, g.mu);
    return line_search(alphak,xk, g.sigma, g.fun, g.dfun);
}
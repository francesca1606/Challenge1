#include "gradientMethod.h"
#include "muParserXFun.hpp"
#include <iostream>
#include <fstream>
#include <math.h>

#include "json.hpp"

using json = nlohmann::json;


Vector gradientMethod::gradient_method(const params_for_GD & g) const{

    Vector xk=g.x0, xk1=g.x0;
    double alphak= g.alpha0;
    int k=0;

    constexpr strategies strat=strategies::exp_decay; 

    for( ; k<=g.max_iter; ++k){
        alphak =  compute_step <strat>(alphak,k, xk, g);  
        xk1= xk - alphak*dfun.evaluate(xk);   //needs to be vector ....
        if((xk1 - xk).norm()< g.tol_x || (dfun.evaluate(xk1) - dfun.evaluate(xk)).norm < g.tol_res)
            break;
        xk=xk1;
    }
    
    return xk1;
}


// IN READ_PARAMS DEVO GIA CONVERTIRE FUN E DFUN ----> BISOGNA ANCHE MODIFCARE LA STRUCT
params_for_GD gradientMethod::read_parameters() const{
  std::ifstream f("data.json");
  json data = json::parse(f);
  
  std::vector<double> x0_v = data["parameters"]["x0"];
  double alpha0 = data["parameters"].value("alpha0", 1.0);
  double tol_res = data["parameters"].value("tol_res", 0.0);
  double tol_x = data["parameters"].value("tol_x", 0.0);
  int max_iter = data["parameters"].value("max_iter", 1);
  double mu = data["parameters"].value("mu", 1.0);
  double sigma = data["parameters"].value("sigma", 1.0);
  std::string f_string=data["functions"].value("f","");
  std::string df_string=data["functions"].value("df","");
  
  muParserXFun fun(f_string);
  muParserXFun dfun(df_string);
  
  return params_for_GD(fun, dfun, Vector(x0_v), alpha0, tol_res, tol_x, max_iter, mu, sigma);
}


double gradientMethod::exp_decay(const int k,const double alpha, const double mu) const{
    return alpha*exp(-mu*k);
}
double gradientMethod::inv_decay(const int k, const double alpha, const double mu) const{
    return alpha/(1+ mu*k);
}
double gradientMethod::line_search(const double alpha, const Vector& xk, const double sigma) const {   //serve qualcosa per leggere funzione
    if(sigma>0 || sigma<0.5){
        const Vector s= xk - alpha*df(xk);
        if ( f(xk) - f(s) >= sigma*alpha*((df(xk)).norm())^2 )
          return alpha;
        else
            return line_search(alpha/2, xk, sigma);
    }
    std::cerr<< "Sigma has to be in the interval (0, 0.5)" << std::endl;
    return ;
}



template<strategies S>
double gradientMethod::compute_step(const double alphak, const int k, const Vector &xk, const params_for_GD &g) const {
    if constexpr(S==strategies::exp_decay)
       return exp_decay(k, alphak, g.mu);
    if constexpr(S==strategies::inv_decay)
       return inv_decay(k, alphak, g.mu);
    return line_search(alphak,xk, g.sigma);
}
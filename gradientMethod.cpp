#include "gradientMethod.hpp"
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
        //alphak= step_method(alphak, flag, k, xk);
        alphak =  compute_step <strat>(alphak,k, xk);  //MODIFICA PERCHè COSI NON VA
        xk1= xk - alphak*eval_df(xk);
        if((xk1 - xk).norm()< g.tol_x || (eval_df(xk1) - eval_df(xk)).norm < g.tol_res)
            break;
        xk=xk1;
    }
    
    return xk1;
}


params_for_GD gradientMethod::read_parameters() const{
  std::ifstream f("data.json");
  json data = json::parse(f);
  params_for_GD g;
  std::vector<double> x0_v = data["parameters"]["x0"];
  g.x0=x0_v;
  g.alpha0 = data["parameters"].value("alpha0", 1.0);
  g.tol_res = data["parameters"].value("tol_res", 0.0);
  g.tol_x = data["parameters"].value("tol_x", 0.0);
  g.max_iter = data["parameters"].value("max_iter", 1);
  g.mu = data["parameters"].value("mu", 1.0);
  g.sigma = data["parameters"].value("sigma", 1.0);
  g.f=data["functions"].value("f","");
  g.df=data["functions"].value("df","");
  return g;
}


double gradientMethod::exp_decay(const int k,const double alpha) const{
    return alpha*exp(-g.mu*k);
}
double gradientMethod::inv_decay(const int k, const double alpha) const{
    return alpha/(1+g.mu*k);
}
double gradientMethod::line_search(const double alpha, const Vector& xk) const {
    if(g.sigma>0 || g.sigma<0.5){
        const Vector s= xk - alpha*eval_df(xk);
        if ( g.f(xk) - g.f(s) >= g.sigma*alpha*((eval_df(xk)).norm())^2 )
          return alpha;
        else
            return line_search(alpha/2, xk);
    }
    std::cerr<< "Sigma has to be in the interval (0, 0.5)" << std::endl;
    return ;
}



template<strategies S>
double gradientMethod::compute_step(const double alphak, const int k, const Vector &xk) const {
    if constexpr(S==strategies::exp_decay)
       return exp_decay(k, alphak);
    if constexpr(S==strategies::inv_decay)
       return inv_decay(k, alphak);
    return line_search(alphak,xk);
}
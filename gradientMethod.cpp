#include "gradientMethod.h"
#include <iostream>
#include <fstream>
#include <math.h>

#include "json.hpp"

using json = nlohmann::json;


Vector gradientMethod::gradient_method(params_for_GD & g) const{

    std::vector<double> xk=g.x0.getPoint(), xk1=g.x0.getPoint();
    double alphak= g.alpha0;
    int k=0;

    constexpr strategies strat=strategies::exp_decay; 

    for( ; k<=g.max_iter; ++k){
        alphak =  compute_step <strat>(alphak,k, xk, g); 

        std::vector<double> norm_gradk(xk.size()), norm_gradk1= norm_gradk;
        for (int i=0; i<xk.size(); ++i){
             xk1[i]= xk[i] - alphak*g.dfun[i].evaluate(xk);
             norm_gradk[i]= g.dfun[i].evaluate(xk);
             norm_gradk1[i]= g.dfun[i].evaluate(xk);
        }
             
        if( Vector(xk1 - xk).norm()< g.tol_x || Vector(norm_gradk1 - norm_gradk).norm() < g.tol_res)   //tutto da rifare
            break;

        xk=xk1;
    }
    
    return xk1;
}


//function that reads from data.json the parameters and returns them inside a params_for_GD object
params_for_GD gradientMethod::read_parameters() const{
  std::ifstream f("data.json");
  json data = json::parse(f);

  params_for_GD g;
  
  std::vector<double> x0_v = data["parameters"]["x0"];
  g.x0=Vector(x0_v);
  g.alpha0 = data["parameters"].value("alpha0", 1.0);
  g.tol_res = data["parameters"].value("tol_res", 0.0);
  g.tol_x = data["parameters"].value("tol_x", 0.0);
  g.max_iter = data["parameters"].value("max_iter", 1);
  g.mu = data["parameters"].value("mu", 1.0);
  g.sigma = data["parameters"].value("sigma", 1.0);
  
  //reading function and gradient (vector of functions)
  std::string f_string=data["functions"].value("f","");
  std::vector<std::string> df_string=data["functions"]["df"];
  g.fun=muParserXFun(f_string);
  for (int i=0; i< df_string.size(); ++i)
       g.dfun[i]= muParserXFun(df_string[i]);
  
  return g;
}


//Strategies to calculate step alphak at each iteration

double gradientMethod::exp_decay(const int k,const double alpha, const double mu) const{
    return alpha*exp(-mu*k);
}
double gradientMethod::inv_decay(const int k, const double alpha, const double mu) const{
    return alpha/(1+ mu*k);
}
double gradientMethod::line_search(const double alpha, const Vector& xk, const double sigma, muParserXFun f, std::vector<muParserXFun> df) const {   //serve qualcosa per leggere funzione
    if(sigma>0 || sigma<0.5){
        std::vector<double> s(xk.size()), normk=s;
        
        for (int i=0; i<xk.size(); ++i){
            normk[i]= df[i].evaluate(xk.getPoint());
            s[i]=  xk[i] - alpha*normk[i];
        }
        
        if ( f.evaluate(xk.getPoint()) - f.evaluate(s) >= sigma*alpha*Vector(normk).norm()*Vector(normk).norm() )
          return alpha;
        else
            return line_search(alpha/2, xk, sigma, f, df);
    }
    std::cerr<< "Sigma has to be in the interval (0, 0.5)" << std::endl;
    return -1. ;
}

template<strategies S>
double gradientMethod::compute_step(const double alphak, const int k, const Vector &xk, const params_for_GD &g) const {
    if constexpr(S==strategies::exp_decay)
       return exp_decay(k, alphak, g.mu);
    if constexpr(S==strategies::inv_decay)
       return inv_decay(k, alphak, g.mu);
    return line_search(alphak,xk, g.sigma, g.fun, g.dfun);
}
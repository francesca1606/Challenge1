//This file contains the methods to initialize the struct params_for_GD
//The user may choose between reading the exact gradient from the provided data.json file
//or the computation of an approximated gradient through finite differences 

#ifndef HH_PARAMETERS_HH
#define HH_PARAMETERS_HH

#include "muParserXFun.hpp"
#include <fstream>
#include "json.hpp"

using Vector=std::vector<double>;
using json = nlohmann::json;



struct params_for_GD{
    muParserXFun fun;
    std::vector <muParserXFun> dfun;
    Vector x0;
    double alpha0, tol_res, tol_x;
    int max_iter;
    double mu, sigma;
};

//reads parameters from a json file (data.json) and returns a params_for_GD object
void read_parameters(params_for_GD & g) {
  std::ifstream f("data.json");
  json data = json::parse(f);

  //params_for_GD g;
  
  Vector x0 = data["parameters"]["x0"];    //perchè è servito farlo????
  g.x0=x0;
  g.alpha0 = data["parameters"].value("alpha0", 1.0);
  g.tol_res = data["parameters"].value("tol_res", 0.0);
  g.tol_x = data["parameters"].value("tol_x", 0.0);
  g.max_iter = data["parameters"].value("max_iter", 1);
  g.mu = data["parameters"].value("mu", 1.0);
  g.sigma = data["parameters"].value("sigma", 1.0);
  
  //reading function and gradient (vector of functions)
  int n= data["functions"].value("dim", 0);
  std::string f_string=data["functions"].value("f","");

  //OPTION FOR GRADIENT!!!!!!!!!!!!!!!!!!!!!!!!!!!
  std::vector<std::string> df_string=data["functions"]["df"];
  

  g.fun=muParserXFun(n,f_string);    
  g.dfun.resize(df_string.size());
  for (int i=0; i< df_string.size(); ++i)
       g.dfun[i]= muParserXFun(n,df_string[i]);
  
};


#endif // HH_PARAMETERS_HH
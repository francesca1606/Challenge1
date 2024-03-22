//This file contains the method to initialize the struct params_for_GD 

#ifndef HH_PARAMETERS_HH
#define HH_PARAMETERS_HH

#include <fstream>
#include "json.hpp"
#include <string>

using Vector=std::vector<double>;
using json = nlohmann::json;



struct params_for_GD{
    std::string f_string;
    std::vector <std::string> df_string;
    Vector x0;
    double alpha0, tol_res, tol_x, epsilon;
    int max_iter, Armijo_iter;
    double mu, sigma;
    int dim;
};

//reads parameters from a json file (data.json) and update a params_for_GD object passed as input
void read_parameters(params_for_GD & g) {
  
  std::ifstream f("data.json");
  
  json data;
  f >> data;
  
  g.x0 = data["parameters"]["x0"].get<Vector>();    
  g.alpha0 = data["parameters"].value("alpha0", 1.0);
  g.tol_res = data["parameters"].value("tol_res", 0.0);
  g.tol_x = data["parameters"].value("tol_x", 0.0);
  g.epsilon = data["parameters"].value("epsilon", 0.0);
  g.max_iter = data["parameters"].value("max_iter", 1);
  g.mu = data["parameters"].value("mu", 1.0);
  g.sigma = data["parameters"].value("sigma", 1.0);
  g.Armijo_iter = data["parameters"].value("Armijo_iter", 1);
  
  //reading function and gradient (vector of functions)
  g.dim= data["functions"].value("dim", 0);
  g.f_string=data["functions"].value("f","");
  g.df_string=data["functions"][("df")].get<std::vector<std::string>>();
  
};


#endif // HH_PARAMETERS_HH
//Useful functions needed to implement the gradient descent method

#ifndef HH_AUXFUNCTIONS_HH
#define HH_AUXFUNCTIONS_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "json.hpp"
#include "muParserXFun.hpp"
#include "parameters.hpp"

//FILES IN FONDO DA ELIMINARE!!!!!!



using Vector=std::vector<double>;
using json = nlohmann::json;


//calculates the norm of a Vector object
double norm (const Vector &v) {
    double res=0;
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
    Vector result=v1;
    if(v1.size()==v2.size())
      for(unsigned int i=0; i<v1.size(); ++i)
          result[i]-= v2[i];
    return result;
};

//product of a Vector with a double
//double*Vector
Vector operator*(double alpha, const Vector &v) {
      std::vector<double> result=v;
      for(auto i: v)
          result[i] *= alpha;
      return result;
};



//Strategies to calculate step alphak at each iteration

enum strategies{
    exponential_decay, inverse_decay, Armijo_rule
};

double exp_decay(const int k,const double alpha, const double mu) {
    return alpha*std::exp(-mu*k);
};

double inv_decay(const int k, const double alpha, const double mu) {
    return alpha/(1+ mu*k);
};

double line_search(const double alpha, const Vector& xk, const double sigma, muParserXFun &f, std::vector<muParserXFun> &df)  {   //serve qualcosa per leggere funzione
    if(sigma>0 || sigma<0.5){
        Vector s(xk.size()), normk=s;
        
        for (unsigned int i=0; i<xk.size(); ++i){
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
};

template<strategies S>
double compute_step(const double alphak, const int k, const Vector &xk, params_for_GD &g, muParserXFun & f, std::vector<muParserXFun> &df)  {
    if constexpr(S==strategies::exponential_decay)
       return exp_decay(k, alphak, g.mu);
    if constexpr(S==strategies::inverse_decay)
       return inv_decay(k, alphak, g.mu);
    return line_search(alphak,xk, g.sigma, f, df);
};



#endif // HH_AUXFUNCTIONS_HH




/*Vector& Vector::operator=(const Vector& v){
      if(&v != this)
          point= v.point;
      return *this;
}

std::vector<double> Vector::getPoint() const{
      return point;
}

void Vector::setPoint(const std::vector<double> &s){
      point=s;
}

//if the index is out of bounds the function returns 0 with a message
double Vector::operator[] (unsigned int n) const{
      if(n< point.size())
         return point[n];
      else{
            std::cout << "index out of bounds";
            return 0.;
      }
}



//returns size of the Vcetor
unsigned int Vector::size() const{
      return point.size();
}



*/
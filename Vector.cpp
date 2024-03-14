#include "Vector.hpp"
#include <math.h>
#include <iostream>


std::vector<double> Vector::getPoint() const{
      return point;
}

void Vector::setPoint(const std::vector<double> &s){
      point=s;
}

double Vector::operator[] (size_t n) const{
      return point[n];
}

//product of a Vector with a scalar (a double)
Vector Vector::operator*(double alpha) const{
      Vector result=*this;
      for(auto &i: result.getPoint()){
          i*=alpha;
      }
      return result;
};

//returns size of the Vcetor
size_t Vector::size() const{
      return point.size();
}

//calculates norm of a Vector
double Vector::norm () const{
    double res=0;
    for(auto &i: point ){
        res += i*i;
    }
    return std::sqrt(res);
}

//prints the elements of Vector on the row
void Vector::print() const{
    for( auto &i: point)
       std::cout << i << " ";
    std::cout << std::endl;
}


//overloading of - operator
//if the sizes of the two vectors don't coincide, the function returns the first vector passed
Vector operator-(const Vector &v1, const Vector &v2){
    std::vector<double> result=v1.getPoint();
    if(v1.size()==v2.size())
      for(auto i: result)
          result[i]-= v2[i];
    return Vector(result);
}


#include "Vector.hpp"
#include <math.h>
#include <iostream>


Vector& Vector::operator=(const Vector& v){
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
      if(n<point.size())
         return point[n];
      else{
            std::cout << "index out of bounds";
            return 0.;
      }
}

//product of a Vector with a scalar (a double)
//Vector*double
Vector Vector::operator*(double alpha) const{
      std::vector<double> result=point;
      for(int i=0; i< point.size(); ++i){
          result[i] *= alpha;
      }
      return Vector(result);
};

//returns size of the Vcetor
unsigned int Vector::size() const{
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
      for(int i=0; i<v1.size(); ++i)
          result[i]-= v2[i];
    return Vector(result);
}


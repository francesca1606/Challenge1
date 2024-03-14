#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vector{
private:
     std::vector<double> point;
     
public:
     Vector()=default;
     Vector(const std::vector<double> &v): point(v) {};

     std::vector<double> getPoint() const;
     void setPoint(const std::vector<double> &s);

     double operator[] (std::size_t n) const;
     Vector operator*(double alpha) const;
     std::size_t size() const;

     double norm() const;
     void print() const;
     

};

//overloading of operators needed for the Gradient Descent Method
Vector operator-(const Vector &v1, const Vector &v2);


#endif /* VECTOR_H */
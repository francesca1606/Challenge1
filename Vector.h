#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vector{
private:
     std::vector<double> point;
     
public:
     Vector()=default;
     Vector(const std::vector<double> &v): point(v) {};

     Vector& operator=(const Vector& v);

     std::vector<double> getPoint() const;
     void setPoint(const std::vector<double> &s);

     double operator[] (unsigned int n) const;
     Vector operator*(double alpha) const;
     unsigned int size() const;

     double norm() const;
     void print() const;
     
};

//overloading of operators needed for the Gradient Descent Method
Vector operator-(const Vector &v1, const Vector &v2);


#endif /* VECTOR_H */
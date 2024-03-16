#include "Vector.hpp"
#include <iostream>
#include <string>
#include "muparser_fun.hpp"



int main () {

    Vector t1({3.,4.,5.});
    t1.print();
    std::cout << t1.norm() << t1[2] << std::endl;

    Vector t2({5,6,7});
    Vector t3= t1*2 -t2;
    t3.print();
    
    std::string funString ="x+y";
    MuparserFun fun(funString);
    double x=fun({5,5});
    std::cout << x << std::endl;

    
     
    return 0;
}
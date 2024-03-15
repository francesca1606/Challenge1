#include "Vector.hpp"
#include <iostream>



int main () {

    Vector t1({3.,4.,5.});
    t1.print();
    std::cout << t1.norm() << t1[2] << std::endl;

    Vector t2({5,6,7});
    Vector t3= t1*2 -t2;
    t3.print();
     
    
    return 0;
}
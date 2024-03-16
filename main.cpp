#include <iostream>
#include <string>
#include "muParserXFun.hpp"
#include "Vector.hpp"

int main () {

    //Vector t1({3.,4.,5.});
    //t1.print();
    //std::cout << t1.norm() << t1[2] << std::endl;

    //Vector t2({5,6,7});
    //Vector t3= t1*2 -t2;
    //t3.print();
    try{
    std::string funString ="1 + 5*x0";
    muParserXFun fun(funString);
    std::vector<double> v({8});
    double x=fun.evaluate(Vector(v).getPoint());
    std::cout << x << std::endl; 
    } catch (const mup::ParserError& e) {
        std::cerr << "Parser error: " << e.GetMsg() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
     
    return 0;
}
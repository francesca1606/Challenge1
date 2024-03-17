#include <iostream>
#include <string>
#include "muParserXFun.hpp"
#include "Vector.h"
#include "gradientMethod.h"

int main () {

    /*params_for_GD g;
    gradientMethod met;
    g= met.read_parameters();*/

    try{
    std::string funString ="1+5*x0";
    muParserXFun fun(funString); /**/
    std::vector<double> v({1});
    double x=fun.evaluate(v);
    std::cout << x << std::endl; 
    } catch (const mup::ParserError& e) {
        std::cerr << "Parser error: " << e.GetMsg() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }



    // read parameters from file
    // call gradient method
    // print solution through Vector print


     
    return 0;
}
#ifndef GRADIENTMETHOD_H
#define GRADIENTMETHOD_H

#include "Vector.h"
#include "muParserXFun.hpp"
#include <string>
#include <vector>


struct params_for_GD{
    muParserXFun fun;
    std::vector <muParserXFun> dfun;
    Vector x0;
    double alpha0, tol_res, tol_x;
    int max_iter;
    double mu, sigma;
};

enum strategies{
    exp_decay, inv_decay, line_search
};


class gradientMethod{

public:

    Vector gradient_method (params_for_GD &g) const;

    //function that reads the parameters of the struct
    params_for_GD read_parameters() const;
    //FUNZIONE CHE LEGGE FUNZIONI
    
    template<strategies S>
    double compute_step (const double alphak, const int k, const Vector &xk, const params_for_GD &g) const;

    double exp_decay(const int k, const double alpha, const double mu) const;
    double inv_decay(const int k, const double alpha, const double mu) const;
    double line_search(const double alpha, const Vector& xk, const double sigma, muParserXFun f, std::vector<muParserXFun> df) const;

};



#endif /* GRADIENTMETHOD_H */
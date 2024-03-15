#ifndef GRADIENTMETHOD_H
#define GRADIENTMETHOD_H

#include "Vector.hpp"


struct params_for_GD{
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

    Vector gradient_method (const params_for_GD &g) const;

    //FUNZIONE CHE LEGGE DATI
    //FUNZIONE CHE LEGGE FUNZIONI
    
    //Vector eval_df(Vector x) const;

    template<strategies S>
    double compute_step (const double alphak, const int k, const Vector &xk) const;

    double exp_decay(const int k, const double alpha) const;
    double inv_decay(const int k, const double alpha) const;
    double line_search(const double alpha, const Vector& xk) const;

};



#endif /* GRADIENTMETHOD_H */
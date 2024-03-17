#ifndef HH_MUPARSERXFUN_H
#define HH_MUPARSERXFUN_H

#include <mpParser.h>
#include <string>
#include "Vector.h"       //vedi se mettere <vector>

class muParserXFun {

private:
    int m_n;
    mup::ParserX m_fun;
    std::string  m_expr;
    std::vector<mup::Value> m_val;
    std::vector<mup::Variable> m_var;
    
public:
    
    // Default constructor
    //muParserXFun(): m_fun(mup::pckALL_NON_COMPLEX), m_n(0) {};     

    // Constructor that takes the domain dimension (# of variables) and the mathematical expression
    muParserXFun(int n,std::string expr) : m_n(n), m_fun(mup::pckALL_NON_COMPLEX), m_expr(expr), m_val(n, 0.0)
    {
        m_fun.SetExpr(expr);
        for (int i=0; i<m_n; ++i){
            m_var.push_back(&m_val[i]);
            std::string varName = "x" + std::to_string(i+1);  
            m_fun.DefineVar(varName, m_var[i]);
        }
    }

    // CONSTRUCTOR IN CASO DI GRADIENTE ....  //però è dare fare per tutte le dimensioni.....
    muParserXFun(muParserXFun f, double epsilon)
    {
         
    }


    

    // Function to evaluate the expression with a given set of variables' values
    double evaluate(const std::vector<double> &x) {
        if(m_n==x.size()) {
        for (int i=0; i<m_n; ++i)
            m_var[i]=x[i];

        // Evaluate the expression
        return m_fun.Eval().GetFloat();
        }
        else {
            std::cerr<<"wrong vector dimensions" <<std::endl;
            return -1.0;
        }
    }
};


#endif /* HH_MUPARSERXFUN_HH */

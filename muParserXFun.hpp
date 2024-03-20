#ifndef HH_MUPARSERXFUN_H
#define HH_MUPARSERXFUN_H

#include <mpParser.h>
#include <string>

using Vector=std::vector<double>;


//CANCELLA SOTTO!!!!!!!!!!!!!!!!!!!!!!!

class muParserXFun {

private:
    int m_n;
    std::string  m_expr;
    std::vector<mup::Value>    m_val;
    std::vector<mup::Variable> m_var;
    mup::ParserX m_fun;
    
public:    

    // Constructor that takes the domain dimension (# of variables) and the mathematical expression
    muParserXFun(int n,std::string expr) : m_n(n), m_fun(mup::pckALL_NON_COMPLEX), m_expr(expr),  m_val(n, mup::Value(0.))
    {
        m_var.reserve(m_n);
        for (int i=0; i<m_n; ++i)
            m_var.emplace_back(&m_val[i]);
            //m_var[i]= &m_val[i];
        for (int i=0; i<m_n; ++i){
            std::string varName = "x" + std::to_string(i+1);  
            m_fun.DefineVar(varName, m_var[i]);
        }
        m_fun.SetExpr(expr);
        std::cout <<"dentro constructor 2" << std::endl;
    };


    // Function to evaluate the expression with a given set of variables' values
    double evaluate(const Vector &x) {
     if(m_n==x.size()) {
         for (int i=0; i<m_n; ++i){
             m_val[i]= x[i]; 
         }

        // Evaluate the expression
        double result;
        try{ result= m_fun.Eval().GetFloat();}
        catch(const mup::ParserError& e) {
        std::cerr << "Parser error: " << e.GetMsg() << std::endl;}
        return result;
        }
        else {
            std::cerr<<"wrong vector dimensions" <<std::endl;
            return -1.0;
        }
    };

};


#endif // HH_MUPARSERXFUN_HH 

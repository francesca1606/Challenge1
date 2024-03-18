#ifndef HH_MUPARSERXFUN_H
#define HH_MUPARSERXFUN_H

#include <mpParser.h>
#include <string>

using Vector=std::vector<double>;


//CANCELLA SOTTO!!!!!!!!!!!!!!!!!!!!!!!

class muParserXFun {

private:
    int m_n;
    mup::ParserX m_fun;
    std::string  m_expr;
    std::vector<mup::Value> m_val;
    std::vector<mup::Variable> m_var;
    
public:
    
    // Default constructor
    muParserXFun(): m_fun(mup::pckALL_NON_COMPLEX), m_n(0) {};     

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


    // Function to evaluate the expression with a given set of variables' values
    double evaluate(const Vector &x) {
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

    ~muParserXFun()= default;

};

// CONSTRUCTOR IN CASO DI GRADIENTE ....  //però è dare fare per tutte le dimensioni.....
/*    muParserXFun(muParserXFun f, int i, double epsilon) : m_n(f.m_n), m_fun(mup::pckALL_NON_COMPLEX), m_val(f.m_n, 0.0) {
    // Initialize the gradient vector with the same size as the function's domain dimension
    std::vector<mup::Value> gradient(m_n, 0.0);


        // Create a copy of the function's values to perturb
        std::vector<double> perturbedValues(m_n, 0.0);          //= f.m_val;

        // Perturb the i-th dimension by epsilon
        perturbedValues[i] += epsilon;

        // Evaluate the function with the perturbed values
        double fPlusH = f.evaluate(perturbedValues);

        // Perturb the i-th dimension by -epsilon
        perturbedValues[i] -=  epsilon*2 ;

        // Evaluate the function with the perturbed values
        double fMinusH = f.evaluate(perturbedValues);

        // Compute the centered difference approximation of the derivative
        gradient[i] = (fPlusH - fMinusH) / (2 * epsilon);
    

    // Convert the gradient vector to a string expression for muParserX
    std::string gradientExpr = "";
    for (int j = 0; j < m_n; ++j) {
        std::string varName = "x" + std::to_string(j+1);
        gradientExpr += varName + "=" + std::to_string(gradient[j].GetFloat()) + ";";
    }

    // Set the gradient expression
    m_fun.SetExpr(gradientExpr);

    // Define the variables for the gradient expression
    for (int j = 0; j < m_n; ++j) {
        std::string varName = "x" + std::to_string(j+1);
        m_fun.DefineVar(varName, m_var[j]);
    }
}*/


#endif // HH_MUPARSERXFUN_HH 

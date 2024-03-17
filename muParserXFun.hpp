#ifndef HH_MUPARSERXFUN_H
#define HH_MUPARSERXFUN_H

#include <mpParser.h>
#include <string>
#include "Vector.h"

class muParserXFun {

private:
    mup::ParserX m_parser;

public:
    
    // Default constructor
    muParserXFun(): m_parser(mup::pckALL_NON_COMPLEX | mup::pckMATRIX) {};

    // Constructor that takes a string representing a mathematical expression
    muParserXFun(const std::string& expr) : m_parser(mup::pckALL_NON_COMPLEX | mup::pckMATRIX) {
        m_parser.SetExpr(expr);
    }

    // Function to evaluate the expression with a given set of variables
    double evaluate(const std::vector<double> &vars) {
        // Assuming the vector elements are to be used as variables in the parser
        for (size_t i = 0; i < vars.size(); ++i) {
            std::string varName = "x" + std::to_string(i);
            //mup::Value val=vars[i];                        //C'è QUALCHE PROBLEMA QUI PER SEGMENTATION FAULT
            //mup::Variable var(varName, val);
            m_parser.DefineVar(varName, mup::Variable(&mup::Value(vars[i])));
        }
        // Evaluate the expression
        double result = m_parser.Eval().GetFloat();

        /*for (size_t i = 0; i < vars.size(); ++i) {
             std::string varName = "x" + std::to_string(i);
             mup::Variable *var = & (m_parser.GetVar(varName));
            if (var) {
            delete var->GetValue(); // Delete the mup::Value object
            var->SetValue(nullptr); // Set the pointer to nullptr to avoid dangling pointer
            }
        }*/

        return result;
    }
};


#endif /* HH_MUPARSERXFUN_HH */

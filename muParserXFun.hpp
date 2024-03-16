#ifndef MUPARSERXFUN_H
#define MUPARSERXFUN_H

#include <mpParser.h>
#include <string>
#include "Vector.h"

class muParserXFun {

private:
    mup::ParserX m_parser;

public:
    // Constructor that takes a string representing a mathematical expression
    muParserXFun(const std::string& expr) : m_parser(mup::pckALL_NON_COMPLEX | mup::pckMATRIX) {
        m_parser.SetExpr(expr);
    }

    // Function to evaluate the expression with a given set of variables
    double evaluate(const std::vector<double> vars) {
        // Assuming the vector elements are to be used as variables in the parser
        for (size_t i = 0; i < vars.size(); ++i) {
            std::string varName = "x" + std::to_string(i);
            mup::Value val=vars[i];                        //C'è QUALCHE PROBLEMA QUI PER SEGMENTATION FAULT
            mup::Variable var(&val);
            m_parser.DefineVar(varName, var);
        }
        // Evaluate the expression
        return m_parser.Eval().GetFloat();
    }
};


#endif /* MUPARSERXFUN_H */

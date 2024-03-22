#ifndef HH_MUPARSERFUN_HH
#define HH_MUPARSERFUN_HH

#include <muParser.h>
#include <string>

using Vector=std::vector<double>;


//Class used to define a parser able to evaluate a function given a vector of doubles
class muParserFun{

private:
    Vector      m_vars;
    std::string m_expr;
    mu::Parser  m_parser;

public:

    muParserFun(int n, const std::string &expression) {
        m_expr=expression;
        m_vars.resize(n);
        for (int i = 0; i < n; ++i) {
            std::string varName = "x" + std::to_string(i+1); 
            m_parser.DefineVar(varName, &m_vars[i]);
        }
        m_parser.SetExpr(expression);
    }

    //evaluates m_parser at vector x
    double operator()(const Vector &x) {

        if (x.size() != m_vars.size()) {
            std::cerr << "Number of variables doesn't match the number of requested variables" << std::endl;
            return std::numeric_limits<double>::quiet_NaN();
        }

        for (unsigned int i = 0; i < x.size(); ++i) 
            m_vars[i] = x[i];

        return m_parser.Eval();
    }


    std::string getExpression() const {
        return m_parser.GetExpr();
    }

};

#endif // HH_MUPARSERFUN_HH

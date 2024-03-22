#ifndef HH_MUPARSERXFUN_HH
#define HH_MUPARSERXFUN_HH

#include <muParser.h>
#include <string>

using Vector=std::vector<double>;


//CANCELLA SOTTO!!!!!!!!!!!!!!!!!!!!!!!

/*class muParserXFun {

private:
    unsigned int m_n;
    //std::string  m_expr;
    //std::vector < mup::Parser> m_grad;
    std::vector<mup::Value>    m_val;
    std::vector<mup::Variable> m_var;
    mup::ParserX m_fun;
    std::vector<mup::ParserX> m_grad;
    
public:    

    // Constructor that takes the domain dimension (# of variables) and the mathematical expression
    muParserXFun(int n,const std::string expr) : m_n(n), m_val(n, mup::Value(0.)), m_fun(mup::pckALL_NON_COMPLEX), m_grad(n,mup::pckALL_NON_COMPLEX)       // m_expr(expr), m_val(n, mup::Value(0.)), m_fun(mup::pckALL_NON_COMPLEX), m_grad(n,mup::pckALL_NON_COMPLEX)
    {
        //m_var.resize(m_n);
        for (unsigned int i=0; i<m_n; ++i)
            m_var.push_back(&m_val[i]);
            //m_var[i]= &m_val[i];
        for (unsigned int i=0; i<m_n; ++i){
            std::string varName = "x" + std::to_string(i+1);  
            m_fun.DefineVar(varName, m_var[i]);
        }
        m_fun.SetExpr(expr);
        std::cout <<"dentro constructor 2" << std::endl;
    };


    // Function to evaluate the expression with a given set of variables' values
    double operator()(const Vector &x) {
     if(m_n==x.size()) {
         for (unsigned int i=0; i<m_n; ++i){
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


    //IN PIù

    void setGrad(const std::vector<std::string> &s_grad ){
        if(m_n==s_grad.size()){
            for (unsigned int i=0; i<m_n; ++i){
                m_grad[i].SetExpr(s_grad[i]);
            }
        }
        else{
            std::cerr<<"wrong vector dimensions" <<std::endl;
        }
    }

    Vector evaluate_dfun(const Vector &x){
        if(m_n==x.size()){
            try{
            for (unsigned int i=0; i<m_n; ++i){
               m_var[i]= x[i]; 
            }
            Vector result(m_n);
            for (unsigned int i=0; i<m_n; ++i){
               result[i]= m_grad[i].Eval().GetFloat(); 
            }
            return result;
            }catch(const mup::ParserError& e) {
             std::cerr << "Parser error: " << e.GetMsg() << std::endl; }
            
        }
        else{
            std::cerr<<"wrong vector dimensions" <<std::endl;
            return Vector({});
        }

    };

};*/
class muParserXFun{
public:
    muParserXFun(int n, const std::string &expression) {
        try {
            m_expression=expression;
            m_vars.resize(n);
            for (int i = 0; i < n; ++i) {
                std::string varName = "x" + std::to_string(i+1); 
                m_parser.DefineVar(varName, &m_vars[i]);
            }
        } catch (mu::Parser::exception_type &e) {
            std::cerr << e.GetMsg() << std::endl;
        }
        m_parser.SetExpr(expression);
    }

    double operator()(const Vector &values) {
        if (values.size() != m_vars.size()) {
            std::cerr << "Number of variables doesn't match the number of requested variables" << std::endl;
            return std::numeric_limits<double>::quiet_NaN();
        }

        for (size_t i = 0; i < values.size(); ++i) {
            m_vars[i] = values[i];
        }

        return m_parser.Eval();
    }

  std::string getExpression() const {
        return m_parser.GetExpr();
    }
private:
    Vector m_vars;
    std::string m_expression;
    mu::Parser m_parser;
};

#endif // HH_MUPARSERXFUN_HH

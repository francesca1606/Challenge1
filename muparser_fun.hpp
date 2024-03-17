#include <mpParser.h>  

#include <memory>
#include <string>
#include <fstream>
#include "Vector.hpp"

//  #include "json.hpp"

//  using json = nlohmann::json;

template <int m_n>
class MuparserXFun
{

private:                         //FORSE è MEGLIO FARLA TEMPLATE CON n PASSATO ESTERNAMENTE
  mup::Value  m_var;
  // int m_n;
  mup::ParserX m_parser;

public:

  //constructor 1  
  MuparserXFun():
    m_parser(mup::pckALL_NON_COMPLEX | mup::pckMATRIX), m_var {m_n, 0.0}
  {
      //std::ifstream f("data.json");
      //json data = json::parse(f);
      //m_n= data["functions"]["n",1];

      //M_parser.DefineVar("x", mup::Variable(&m_var));
      for (int i=0; i < m_n ; ++i)
           m_parser.DefineVar("x"+ std::to_string(i), & m_var.At(i));
  };
  
  //constructor taking as input a string
  MuparserXFun(const std::string &expr): MuparserXFun() 
  {
        //std::ifstream f("data.json");   ////lo passo da json???? o da main forse è meglio
        //json data = json::parse(f);
        //m_n= data["functions"]["n",1];

        for (int i=0; i< m_n ; ++i)
           m_parser.DefineVar("x"+ std::to_string(i), &m_var.At(i));
        m_parser.SetExpr(expr.c_str());
  };

  // evaluating function
  auto
  operator()(const std::vector<double> &x)   //deve essere Vector
  {
    for (int i=0; i< m_n; ++i)
       m_var.At(i) = x[i];    
    mup::Value y = m_parser.Eval();   
    return y.GetFloat();
  };

};

#ifndef PARCE_H
#define PARCE_H 1

#include <functional>
#include <string>


using func = std::function<double (double, double, double)>;
using scalar_f = std::function<double(double)>;

class Token_error
{
private:
  std::string message;
  
public:
  Token_error(std::string m) { message = m; }

  std::string what() { return message; }
};

func get_function(std::string); //FIXME Grammar.h

#endif    // PARCE_H

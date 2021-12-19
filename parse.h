#ifndef PARSE_H
#define PARSE_H 1

#include <functional>
#include <string>


using func = std::function<double (double, double, double)>;


class Token_error
{
private:
  std::string message;
  
public:
  Token_error(std::string m) { message = m; }

  std::string what() { return message; }
};

func get_function(std::string&); 

#endif    // PARSE_H

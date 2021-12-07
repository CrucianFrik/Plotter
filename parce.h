#ifndef PARCE_H
#define PARCE_H 1

#include <functional>
#include <string>

#include <iostream>
#define DEBUG_OUT(x) std::cout << "Debug_out: " << __FILE__ << " " << __func__  << " " << __LINE__ << ": "<< (#x) << " = " << x << "\n"

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

#endif    // PARCE_H

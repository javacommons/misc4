#include "calc.hpp"
#include "vardecl.h"
#include <string>

#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include "base64.hpp"

int add(int x, int y)
{
  return x + y;
}

int sub(int x, int y)
{
  return x - y;
}

void ref1(int *ret)
{
  *ret = 1234;
}

const char *ret_str()
{
  return "helloハロー";
}

const char *hello(const char *name)
{
  static TLS_VARIABLE_DECL std::string msg;
  msg = "こんにちは ";
  msg += name;
  return msg.c_str();
}

api1_output api1(const api1_input &input)
{
  //double a = input.a;
  //double b = input.b;
  //std::cout << a << std::endl;
  //std::cout << b << std::endl;
  api1_output result;
  result.sum = input.a + input.b;
  result.diff = input.a - input.b;
  return result;
}

double sum(const std::vector<double> &args)
{
  double result;
  for (auto it = args.begin(); it != args.end(); ++it)
  {
    double d = *it;
    result += d;
  }
  return result;
}

const char *apicall(const char *name, const char *base64_args)
{
  std::string api_name = name;
  //std::string result = pack_api_result(0);
  std::string packed_result = pack_result(false);
  std::string packed = base64_decode(std::string(base64_args));
  msgpack::object_handle oh =
      msgpack::unpack(packed.data(), packed.size());
  msgpack::object args = oh.get();
  std::cout << "API=" << api_name << " args=" << args << std::endl;
  if (api_name == "api1")
  {
    api1_input input(args);
    api1_output result = api1(input);
    packed_result = pack_result(result);
  }
  else if (api_name == "sum")
  {
    std::vector<double> input;
    args.convert(input);
    double result = sum(input);
    packed_result = pack_result(result);
  }
  static TLS_VARIABLE_DECL std::string base64_result;
  base64_result = base64_encode(packed_result);
  return base64_result.c_str();
}
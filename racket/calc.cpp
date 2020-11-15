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

struct api1_input_type
{
  double a;
  double b;
  MSGPACK_DEFINE(a, b);
  api1_input_type(const msgpack::object &args)
  {
    ARGS_AS_MAP mmap = args.as<ARGS_AS_MAP>();
    double a = mmap.find("a")->second.as<double>();
    double b = mmap.find("b")->second.as<double>();
    this->a = a;
    this->b = b;
  }
};
struct api1_result_type
{
  double sum;
  double diff;
  MSGPACK_DEFINE(sum, diff);
};
std::string api1(const msgpack::object &args)
{
#if 0x1
  ARGS_AS_MAP mmap = args.as<ARGS_AS_MAP>();
  double a = mmap.find("a")->second.as<double>();
  double b = mmap.find("b")->second.as<double>();
#else
  api1_input_type input;
  //args.convert(input);
  input = args.as<api1_input_type>();
  double a = input.a;
  double b = input.b;
#endif
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  api1_result_type result;
  result.sum = a + b;
  result.diff = a - b;
  return pack_result(result);
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
    packed_result = api1(args);
  }
  else if (api_name == "sum")
  {
    std::vector<double> api_args;
    args.convert(api_args);
    packed_result = pack_result(sum(api_args));
  }
  static TLS_VARIABLE_DECL std::string base64_result;
  base64_result = base64_encode(packed_result);
  return base64_result.c_str();
}
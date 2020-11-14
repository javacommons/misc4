#include "calc.hpp"
#include "vardecl.h"
#include <string>

#include <msgpack.hpp>
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
  static TLS_VARIABLE_DECL std::string msg = "こんにちは ";
  msg += name;
  return msg.c_str();
}

typedef std::map<std::string, msgpack::object> ARGS_AS_MAP;
typedef std::vector<msgpack::object>           ARGS_AS_VECTOR;

template <typename T>
std::string pack_api_result(T x)
{
  std::stringstream buffer;
  msgpack::pack(buffer, x);
  buffer.seekg(0);
  std::string str(buffer.str());
  return str;
}

struct api1_result_type
{
  double sum;
  double diff;
  MSGPACK_DEFINE(sum, diff);
};
std::string api1(const msgpack::object &args)
{
  ARGS_AS_MAP mmap = args.as<ARGS_AS_MAP>();
  double a = mmap.find("a")->second.as<double>();
  double b = mmap.find("b")->second.as<double>();
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  api1_result_type result;
  result.sum = a + b;
  result.diff = a - b;
  return pack_api_result(result);
}

std::string sum(const msgpack::object &args)
{
  ARGS_AS_VECTOR mvect = args.as<ARGS_AS_VECTOR>();
  std::cout << mvect.size() << std::endl;
  return  pack_api_result(0);
}

const char *apicall(const char *name, const char *base64_args)
{
  std::string api_name = name;
  std::string result;
  //std::cout << "(1)" << std::endl;
  //std::cout << "(2)" << std::endl;
  std::string packed = base64_decode(std::string(base64_args));
  msgpack::object_handle oh =
      msgpack::unpack(packed.data(), packed.size());
  //std::cout << "(3)" << std::endl;
  msgpack::object args = oh.get();
  //std::cout << "(4)" << std::endl;
  std::cout << "API=" << api_name << " args=" << args << std::endl;
  if (api_name == "api1")
  {
    result = api1(args);
  }
  else if (api_name == "sum")
  {
    result = sum(args);
  }
  static TLS_VARIABLE_DECL std::string base64_result = base64_encode(result);
  std::cout << "base64_result=" << base64_result << std::endl;
  return base64_result.c_str();
}
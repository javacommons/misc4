#include "calc.exp.hpp"
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

typedef std::map<std::string, msgpack::object> MapStrMsgpackObj;

template<typename T>
std::string pack_api_result(T x) {
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
std::string api1(const MapStrMsgpackObj &args)
{
  double a = args.find("a")->second.as<double>();
  double b = args.find("b")->second.as<double>();
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  api1_result_type result;
  result.sum = a + b;
  result.diff = a - b;
  return pack_api_result(result);
  #if 0x0
  std::stringstream buffer;
  msgpack::pack(buffer, result);
  buffer.seekg(0);
  std::string str(buffer.str());
  return str;
  #endif
}

const char *apicall(const char *name, const char *base64_args)
{
  std::string api_name = name;
  std::string result;
  std::string packed = base64_decode(std::string(base64_args));
  msgpack::object_handle oh =
      msgpack::unpack(packed.data(), packed.size());
  msgpack::object obj = oh.get();
  MapStrMsgpackObj args = obj.as<MapStrMsgpackObj>();
  if (api_name == "api1")
  {
    result = api1(args);
  }
  std::string base64_result = base64_encode(result);
  return base64_result.c_str();
}
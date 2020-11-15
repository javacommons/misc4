#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "calc.hpp"
#include "vardecl.h"
#include <string>

#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <exception>
#include "base64.hpp"

#include <time.h>
#include <assert.h>

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
  api1_output output;
  output.sum = input.a + input.b;
  output.diff = input.a - input.b;
  time_t t = time(NULL);
  struct tm tm;
  char str[81];
  localtime_s(&tm, &t);
  strftime(str, sizeof(str), "%Y-%m-%d %H:%I:%S", &tm);
  printf("%s\n", str);
  output.ts = str;
  output.bin.push_back(0);
  output.bin.push_back(1);
  output.bin.push_back(2);
  return output;
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
  MsgPack dummy = false;
  std::string packed_result = dummy.dump();
  std::string packed = base64_decode(std::string(base64_args));
  json json1 = json::from_msgpack(packed);
  std::cout << "[API]" << api_name << " args=" <<  json1.dump() << std::endl;
  std::string err;
  MsgPack obj = MsgPack::parse(packed, err);
  if (err != "")
    printf("err=[%s]\n", err.c_str());
  if (api_name == "api1")
  {
    api1_input input(obj);
    api1_output result = api1(input);
    packed_result = result.pack();
  }
  else if (api_name == "sum")
  {
    if (!obj.is_array())
    {
      std::cout << "[api] " << api_name << std::endl;
      show(obj);
      //throw std::exception();
      exit(1);
    }
    std::vector<double> input;
    auto array = obj.array_items();
    for (auto it = array.begin(); it != array.end(); ++it)
    {
      input.push_back(it->float64_value());
    }
    MsgPack result = sum(input);
    packed_result = result.dump();
  }
  static TLS_VARIABLE_DECL std::string base64_result;
  base64_result = base64_encode(packed_result);
  return base64_result.c_str();
}
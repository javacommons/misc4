#ifdef __cplusplus
extern "C"
{
#endif

  int add(int x, int y);
  int sub(int x, int y);
  void ref1(int *ret);
  const char *ret_str();
  const char *hello(const char *name);
  const char *apicall(const char *name, const char *base64_args);

#ifdef __cplusplus
} // extern "C" {
#endif

#ifdef __cplusplus

#include <msgpack.hpp>
#include "msgpack11.hpp"
using namespace msgpack11;

#include "msgpack11_dump.hpp"

#include <iostream>

typedef std::map<std::string, msgpack::object> ARGS_AS_MAP;
typedef std::vector<msgpack::object> ARGS_AS_VECTOR;

template <typename T>
std::string pack_result(T x)
{
  std::stringstream buffer;
  msgpack::pack(buffer, x);
  buffer.seekg(0);
  return buffer.str();
}

struct api1_input
{
  double a;
  double b;
  MSGPACK_DEFINE(a, b);
#if 0x0
  api1_input(const msgpack::object &args)
  {
    ARGS_AS_MAP mmap = args.as<ARGS_AS_MAP>();
    double a = mmap.find("a")->second.as<double>();
    double b = mmap.find("b")->second.as<double>();
    this->a = a;
    this->b = b;
  }
#endif
  api1_input(const MsgPack &obj)
  {
    double a = obj["a"].float64_value();
    double b = obj["b"].float64_value();
    this->a = a;
    this->b = b;
  }
};
struct api1_output
{
  double sum;
  double diff;
  std::string ts;
  //MSGPACK_DEFINE(sum, diff, ts);
  std::string pack()
  {
    MsgPack obj = MsgPack::object{
        {"sum", this->sum},
        {"diff", this->diff},
        {"ts", this->ts}};
    return obj.dump();
  }
  std::string pack_test()
  {
    MsgPack obj = MsgPack::object{
        {"key1", "value1"},
        {"key2", false},
        {"key3", MsgPack::array{1, 2, 3}},
        {"key4", MsgPack::object{
                     {"key4-a", 1024},
                     {"key4-b", MsgPack::binary{0, 2, 4, 6}}}},
        {"key5", MsgPack::array{MsgPack::object{{"key5-1-a", 100}, {"key5-1-b", 200}}, MsgPack::object{{"key5-2-a", 300}, {"key5-2-b", 400}}}}};
    std::cout << "---- original ----" << std::endl;
    show(obj);
    std::cout << obj["key1"].string_value() << std::endl;
    std::cout << obj["key2"].string_value() << std::endl;
    std::cout << obj["key2"].bool_value() << std::endl;
    show(obj["key3"]);
    std::cout << obj["key3"].array_items().size() << std::endl;
    std::cout << obj["key3"].array_items()[2].int64_value() << std::endl;
    std::cout << obj["key3"].array_items()[2].type() << std::endl;
    std::string err;
    MsgPack serdes_obj = MsgPack::parse(obj.dump(), err);
    std::cout << "---- ser/des result ----" << std::endl;
    show(serdes_obj);
    MsgPack obj2 = MsgPack::array{110, 220, 330};
    show(obj2);
    return "";
  }
};
api1_output api1(const api1_input &input);

double sum(const std::vector<double> &args);

#endif
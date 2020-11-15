#ifdef __cplusplus
extern "C" {
#endif

int add(int x, int y);
int sub(int x, int y);
void ref1(int *ret);
const char* ret_str();
const char *hello(const char *name);
const char *apicall(const char *name, const char *base64_args);

#ifdef __cplusplus
} // extern "C" {
#endif

#ifdef __cplusplus

#include <msgpack.hpp>

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
  api1_input(const msgpack::object &args)
  {
    ARGS_AS_MAP mmap = args.as<ARGS_AS_MAP>();
    double a = mmap.find("a")->second.as<double>();
    double b = mmap.find("b")->second.as<double>();
    this->a = a;
    this->b = b;
  }
};
struct api1_output
{
  double sum;
  double diff;
  MSGPACK_DEFINE(sum, diff);
};
api1_output api1(const api1_input &input);

double sum(const std::vector<double> &args);

#endif
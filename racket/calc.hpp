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
std::string pack_api_result(T x)
{
  std::stringstream buffer;
  msgpack::pack(buffer, x);
  buffer.seekg(0);
  return buffer.str();
}

#endif
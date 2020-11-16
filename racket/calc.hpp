#ifndef CALC_HPP
#define CALC_HPP

#include <windows.h>

#ifdef __cplusplus
extern "C"
{
#endif

  unsigned long long open_pipe_server(const char *name,
                                      const char *client,
                                      int show_client);
  unsigned long long open_pipe_client(const char *name);
  const char *read_from_pipe(unsigned long long hPipe);
  void write_to_pipe(unsigned long long hPipe, const char *s);
  unsigned long long ret_addr();

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

#include <string>

static inline std::string unsigned_to_string(unsigned long long n)
{
    return std::to_string(n);
}

static inline unsigned long long string_to_unsigned(const std::string &s)
{
    return std::stoull(s);
}

static inline std::string address_to_string(void *p)
{
    unsigned long long n = (unsigned long long)p;
    return std::to_string(n);
}

static inline void *string_to_address(const std::string &s)
{
    return (void *)std::stoull(s);
}

#endif // __cplusplus

#endif // CALC_HPP

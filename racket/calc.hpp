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

#endif //CALC_HPP

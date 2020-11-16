#include "calc.hpp"

//#include <nlohmann/json.hpp>
//using json = nlohmann::json;

#include <string>
#include <iostream>

#include "pipe.hpp"
#include "strconv.h"
#include "vardecl.h"

const char *open_pipe_server(const char *prefix,
                                    const char *client,
                                    int show_client)
{
  FILETIME file_time;
  GetSystemTimeAsFileTime(&file_time);
  ULONGLONG ull = (ULONGLONG)file_time.dwHighDateTime << 32 | file_time.dwLowDateTime;
  std::string name = prefix;
  name += ":";
  name += std::to_string(ull);

  //client_program = client;
  //std::cout << "(1)" << std::endl;
  HANDLE hPipe = create_pipe_server(name, 4096);
  //std::cout << "(2)" << std::endl;
  if (hPipe == INVALID_HANDLE_VALUE)
  {
    //std::cout << "(3)" << std::endl;
    MessageBoxW(NULL, L"サーバーパイプの作成に失敗しました。", NULL, MB_ICONWARNING);
    return "";
  }
  std::wstring cmdline = utf8_to_wide(client);
  cmdline += L" ";
  cmdline += utf8_to_wide(name);
  std::cout << wide_to_utf8(cmdline) << std::endl;
  PROCESS_INFORMATION ps = {0};
  /*static TLS_VARIABLE_DECL*/ STARTUPINFOW si = {0};
  std::cout << "(1)" << std::endl;
  WINBOOL b = CreateProcessW(
      NULL,
      (LPWSTR)cmdline.c_str(),
      NULL,
      NULL,
      FALSE,
      show_client ? 0 : CREATE_NO_WINDOW,
      NULL,
      NULL,
      &si,
      &ps);
  std::cout << "(2)" << std::endl;
  if (!b)
  {
    std::cout << "(3)" << std::endl;
    std::cout << "Could not start client." << std::endl;
    exit(1);
  }
  std::cout << "(4)" << std::endl;
  //std::cout << "(4)" << std::endl;
  ConnectNamedPipe(hPipe, NULL);
  //std::cout << "(5)" << std::endl;
  static TLS_VARIABLE_DECL std::string addr = address_to_string(hPipe);
  return addr.c_str();
}

const char *open_pipe_client(const char *name)
{
  HANDLE hPipe = create_pipe_client(name);
  static TLS_VARIABLE_DECL std::string addr = address_to_string(hPipe);
  return addr.c_str();
}

const char *read_from_pipe(const char *hPipe)
{
  static TLS_VARIABLE_DECL std::string read;
  read = read_string_from_pipe(string_to_address(hPipe));
  return read.c_str();
}

void write_to_pipe(const char *hPipe, const char *s)
{
  write_string_to_pipe(string_to_address(hPipe), s);
}

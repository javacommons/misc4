#include "pipe.hpp"
#include "vardecl.h"
#include "strconv.h"

#include <windows.h>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "base64.hpp"

int main(int argc, char *argv[])
{
    const char *name = argv[1];

    char szData[] = "sample-data";

    HANDLE hPipe = create_pipe_crient(name);
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        MessageBoxW(NULL, L"パイプへの接続に失敗しました。",
                    NULL, MB_ICONWARNING);
        return 0;
    }

    write_string_to_pipe(hPipe, szData);
    std::string read = read_string_from_pipe(hPipe);
    std::string packed = base64_decode(read);
    json json1 = json::from_msgpack(packed);
    //std::cout << "[API]" << api_name << " args=" << json1.dump() << std::endl;

    MessageBoxW(NULL, utf8_to_wide(json1.dump(4)).c_str(), L"クライアント", MB_OK);

    CloseHandle(hPipe);

    return 0;
}

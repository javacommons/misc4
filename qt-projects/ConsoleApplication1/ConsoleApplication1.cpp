#include "../common/strconv2.hpp"
#include <iostream>
#include <fstream> //  ifstream, ofstream
#include <stdio.h>
#include <windows.h>
#include <psapi.h>

using namespace std;
using namespace strconv2;
//using strconv2::utf8_to_sjis;

std::string ProcessIdToName(DWORD processId)
{
    std::string ret;
    HANDLE handle = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        processId /* This is the PID, you can find one from windows task manager */
    );
    if (handle)
    {
        DWORD buffSize = 1024;
        CHAR buffer[1024];
        if (QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
        {
            ret = buffer;
        }
        else
        {
            printf("Error GetModuleBaseNameA : %lu", GetLastError());
        }
        CloseHandle(handle);
    }
    else
    {
        printf("Error OpenProcess : %lu", GetLastError());
    }
    return ret;
}

int main()
{
    string_io io;
    io._dump();

    HWND hwnd = GetConsoleWindow();
    io.printf(u8"hwnd=%p\n", hwnd);
    if (hwnd) {
        std::wstring text(4096, L'\0');
        int r = GetWindowTextW(
            hwnd,
            &text[0],
            text.length()
        );
        DWORD err = GetLastError();
        io.printfW(L"r=%d err=%u text=%s\n", r, err, text.c_str());
        DWORD proc_id;
        DWORD th_id = GetWindowThreadProcessId(hwnd, &proc_id);
        io.printf("proc_id=%u\n", proc_id);
        io.printf("ProcessIdToName(proc_id)=%s\n", ProcessIdToName(proc_id).c_str());
    }

    cout << "Hello World!(3)" << endl;
    wstring wide = L"abc漢字©";
    io.printfW(L"wide.c_str()=%s\n", wide.c_str());
    wstring w2 = io.promptW(L"wide入力: ");
    io.printfW(L"w2=%s\n", w2.c_str());
    string sjis = io.promptJ("sjis入力: ");
    io.printfJ("sjis=%s\n", sjis.c_str());

    cout << io.setenv(u8"AAA", u8"=xyz変数©") << endl;
    io.write("AAA=");
    io.writeln(io.getenv("AAA"));
    io.writeln(io.getenv("PATH"));

    ifstream fin;
    fin.open("input1.txt");
    io.set_in_stream(fin);
    std::string line;
    while (io.getline(line)) {
        io.writelnJ("success");
        io.writeln(line);
    }
    fin.close();

    return 0;
}

#include "strconv2.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace strconv2;
//using strconv2::utf8_to_sjis;

int main()
{
    string_io io;
    cout << io.m_console_codepage << endl;
    cout << "Hello World!(3)" << endl;
    std::string utf8 = "abc漢字©";
    cout << utf8 << endl;
    cout << utf8_to_sjis( utf8 ) << endl;
    wstring wide = L"abc漢字©";
    io.printfW(L"%s\n", wide.c_str());
    string sjis = io.getsJ(wide_to_sjis(L"abc入力: "));
    io.writelnJ(sjis);
    wstring w2 = io.getsW(L"wide入力: ");
    io.writelnW(w2);

    return 0;
}

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <stdio.h>
#include "strconv.h"

#include "pipe.hpp"

namespace ns
{
    // a simple struct to model a person
    struct person
    {
        std::string name;
        std::string address;
        int age;
    };
} // namespace ns

namespace ns
{
    void to_json(json &j, const person &p)
    {
        j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
    }

    void from_json(const json &j, person &p)
    {
        j.at("name").get_to(p.name); // get_to(T& arg) は arg = get<T>() と同じ
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }
} // namespace ns

json api_persons(/*const json &input*/)
{
    //std::cout << "[api_persons] input=" << input << std::endl;
    typedef std::vector<ns::person> person_vec;
    person_vec vec;
    vec.push_back(ns::person{"Ned Flanders", "744 Evergreen Terrace", 60});
    vec.push_back(ns::person{"Ned2 Flanders", "7442 Evergreen Terrace", 602});
    json j = vec;
    return j;
}

int handle_pipe_events(const std::string &pipe_name)
{
    HANDLE hPipe = create_pipe_client(pipe_name);
    while (true)
    {
        std::string input_json = read_string_from_pipe(hPipe);
        std::cout << "input_json=" << input_json << std::endl;
        if (input_json.empty())
            break;
        json packet = json::parse(input_json);
        std::string api_name = packet["name"];
        json value = packet["value"];
        std::cout << api_name << " " << value << std::endl;
        json output = api_persons();
        std::cout << output << std::endl;
        write_string_to_pipe(hPipe, output.dump());
    }
    return 0;
}

static inline std::string unsigned_to_string(unsigned long long n)
{
    return std::to_string(n);
}

static inline unsigned long long string_to_unsigned(const std::string &s)
{
    return std::stoull(s);
}

#if 0x1
static inline void *unsigned_to_address(unsigned long long n)
{
    return (void *)n;
}

static inline unsigned long long address_to_unsigned(void *p)
{
    return (unsigned long long)p;
}
#endif

static inline std::string address_to_string(void *p)
{
    unsigned long long n = (unsigned long long)p;
    return std::to_string(n);
}

static inline void *string_to_address(const std::string &s)
{
    return (void *)std::stoull(s);
}

extern "C" void __wgetmainargs(int *, wchar_t ***, wchar_t ***, int, int *);
int main(int, char **)
{
    int argc, si = 0;
    wchar_t **argv, **env;
    __wgetmainargs(&argc, &argv, &env, 0, &si);
    printf("argc=%d\n", argc);
    if (argc >= 2)
    {
        std::string pipe_name = wide_to_utf8(argv[1]).c_str();
        printf("pipe_name=%s\n", pipe_name.c_str());
        return handle_pipe_events(pipe_name);
    }
    std::cout << "(1)" << std::endl;
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
    std::cout << "(2)" << std::endl;
    json j = p; // jsonへの暗黙的変換
    std::cout << "(3)" << std::endl;
    std::cout << j << std::endl;
    std::cout << "(4)" << std::endl;
    // {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}
    ns::person p2 = j.get<ns::person>(); // json->personへの変換
    std::cout << "(5)" << std::endl;

    json output = api_persons();
    std::cout << output << std::endl;

    auto n = 18446744073709551615ULL;
    std::string s = unsigned_to_string(n);
    std::cout << s << std::endl;
    unsigned long long ull = string_to_unsigned(s);
    std::cout << ull << std::endl;

    void *addr = unsigned_to_address(ull);
    auto ull2 = address_to_unsigned(addr);
    std::cout << ull2 << std::endl;

    std::cout << address_to_string(addr) << std::endl;

    void *addr2 = string_to_address(s);
    std::cout << address_to_string(addr2) << std::endl;

    HANDLE hdl = addr2;

    return 0;
}

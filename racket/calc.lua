-- premake4.lua
solution "Hello Premake"

  configurations { "Release", "Debug" }

  project "calc"
    -- https://github.com/premake/premake-core/wiki/kind
    kind "SharedLib"
    language "C++"
    files {
      -- "base64.hpp",
      "calc.hpp",
      -- "msgpack11.hpp", "msgpack11_dump.hpp",
      "vardecl.h",
      -- "base64.cpp",
      "calc.cpp"
      -- , "msgpack11.cpp", "msgpack11_dump.cpp"
      }
    buildoptions { "-std=c++17" }
    includedirs {
      -- ".."
    }
    libdirs {
      -- ".."
    }
    links {
      "opengl32", "glu32"
    }
    linkoptions { "-static", "-Wl,-allow-multiple-definition" }
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }
      targetsuffix "-d"

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }

#! bash -uvx
premake4 --file=calc.lua gmake
rm -rf obj
make

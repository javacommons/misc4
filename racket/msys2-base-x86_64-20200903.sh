#! bash -uvx
raco exe --gui -o msys2-base-x86_64-20200903-my-setup.exe msys2-base-x86_64-20200903.rkt
raco distribute inst.tmp msys2-base-x86_64-20200903-my-setup.exe
cp -p msys2-base-x86_64-20200903.zip inst.tmp
cp -p .emacs inst.tmp
cp -p c-quick-2.el inst.tmp


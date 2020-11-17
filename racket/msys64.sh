#! bash -uvx
raco exe --gui -o msys64-my-setup.exe msys64.rkt
raco distribute inst.tmp msys64-my-setup.exe
cp -p msys64.zip inst.tmp
cp -p .emacs inst.tmp
cp -p c-quick-2.el inst.tmp

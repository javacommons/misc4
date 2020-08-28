#! bash -uvx
bash ../install-qt.sh
bash ../install-libs.sh
rm -rf .qmake* debug release Makefile* *_plugin_import.cpp ui_*.h
$MSYSTEM_PREFIX/qt5-static/bin/qmake *.pro
mingw32-make -f Makefile.Release all post
rm release/*.h
rm release/*.cpp
rm release/*.moc
rm release/*.o
mkdir -p release/output
/c/Users/Public/install/BoxedAppPacker_2020_5_0_0/BoxedAppPackerConsole.exe temp01.bxproj | iconv -f cp932 -t utf-8

cd buildD/
cmake -j4 -DCMAKE_EXE_LINKER_FLAGS="-static-libstdc++ -static-libgcc" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DwxWidgets_ROOT_DIR:PATH="C:\Cpp\wxWidgets" -DEXTERN_DIR:PATH="%UserProfile%" ../
mingw32-make
PAUSE

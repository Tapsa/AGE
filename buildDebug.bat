cd buildD/
cmake -DCMAKE_EXE_LINKER_FLAGS="-static-libstdc++ -static-libgcc -static" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Debug -DwxWidgets_ROOT_DIR:PATH="C:\Cpp\wxWidgets" -DBOOST_LIBRARYDIR:PATH="C:\Cpp\Boost\lib" -DBOOST_INCLUDEDIR:PATH="C:\Cpp\Boost\include" -DZLIB_LIBRARY:FILEPATH="C:\Cpp\zlib\libz.a" -DZLIB_INCLUDE_DIR:PATH="C:\Cpp\zlib" ../
mingw32-make
PAUSE

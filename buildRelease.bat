cd build/
cmake -DCMAKE_EXE_LINKER_FLAGS="-static-libstdc++ -static-libgcc --disable-shared --enable-static" -DCMAKE_SHARED_LINKER_FLAGS="-static-libstdc++ -static-libgcc --disable-shared --enable-static" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DwxWidgets_ROOT_DIR:PATH="C:\Cpp\wxWidgets" -DBOOST_LIBRARYDIR:PATH="C:\Cpp\boost_libs" -DBOOST_ROOT:PATH="C:\Cpp\boost_1_47_0" -DZLIB_LIBRARY:FILEPATH="C:\Cpp\zlib\libz.a" -DZLIB_INCLUDE_DIR:PATH="C:\Cpp\zlib" ../
mingw32-make
cd ..
cd ..
copy "sources\build\AdvancedGenieEditor2.exe" "AGE2\AdvancedGenieEditor2.exe"
cd AGE2
strip *
upx --best *
PAUSE
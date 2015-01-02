cd buildR/
cmake -j4 -DCMAKE_EXE_LINKER_FLAGS="-static-libstdc++ -static-libgcc -static" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release -DwxWidgets_ROOT_DIR:PATH="C:\Cpp\wxWidgets" -DBOOST_LIBRARYDIR:PATH="C:\Cpp\Boost\lib" -DBOOST_INCLUDEDIR:PATH="C:\Cpp\Boost\include" -DZLIB_LIBRARY:FILEPATH="C:\Cpp\zlib\libz.a" -DZLIB_INCLUDE_DIR:PATH="C:\Cpp\zlib" -DEXTERN_DIR:PATH="C:\Users\Tapsa" ../
mingw32-make
cd ..
cd ..
copy "sources\buildR\AdvancedGenieEditor3.exe" "AGE2\AdvancedGenieEditor3.exe"
cd AGE2
strip Adv*
::upx --best *
PAUSE

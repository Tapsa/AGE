cd buildR/
cmake -j4 -DCMAKE_EXE_LINKER_FLAGS="-static-libstdc++ -static-libgcc -static" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DwxWidgets_ROOT_DIR:PATH="C:\Cpp\wxWidgets" -DEXTERN_DIR:PATH="C:\Users\Tapsa" ../
mingw32-make
copy "AdvancedGenieEditor3.exe" "C:\Juttu\AGE\AGE2\AdvancedGenieEditor3.exe"
cd "C:\Juttu\AGE\AGE2"
strip Adv*
::upx --best *
PAUSE

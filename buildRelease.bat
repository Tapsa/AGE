cd buildR/
SET wxWidgetsRF="C:\Cpp\wxWidgets"
SET zlibIF="C:\Cpp\mingw-w64\mingw32\i686-w64-mingw32\include"
SET zlibLL="C:\Cpp\mingw-w64\mingw32\i686-w64-mingw32\lib\libz.a"
SET iconvIF="C:\Cpp\mingw-w64\mingw32\i686-w64-mingw32\include"
SET iconvLL="C:\Cpp\mingw-w64\mingw32\i686-w64-mingw32\lib\libiconv.a"
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DwxWidgets_ROOT_DIR:PATH="%wxWidgetsRF%" -DZLIB_INCLUDE_DIR="%zlibIF%" -DZLIB_LIBRARY="%zlibLL%" -DICONV_INCLUDE_DIR="%iconvIF%" -DICONV_LIBRARIES="%iconvLL%" -DEXTERN_DIR:PATH="%UserProfile%" ../
mingw32-make -j4
strip AdvancedGenieEditor3.exe
copy "AdvancedGenieEditor3.exe" "C:\Juttu\AGE\AGE2\AdvancedGenieEditor3.exe"
cd "C:\Juttu\AGE\AGE2"
::upx --best *
PAUSE

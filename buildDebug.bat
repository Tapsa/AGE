CD debug/
SET wxWidgetsRF="C:/Cpp/wxWidgets"
SET zlibIF="C:/Cpp/mingw-w64/mingw32/i686-w64-mingw32/include"
SET zlibLL="C:/Cpp/mingw-w64/mingw32/i686-w64-mingw32/lib/libz.a"
SET iconvIF="C:/Cpp/mingw-w64/mingw32/i686-w64-mingw32/include"
SET iconvLL="C:/Cpp/mingw-w64/mingw32/i686-w64-mingw32/lib/libiconv.a"
SET SFMLRF="C:/Cpp/SFML"
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DwxWidgets_ROOT_DIR:PATH="%wxWidgetsRF%" -DZLIB_INCLUDE_DIR="%zlibIF%" -DZLIB_LIBRARY="%zlibLL%" -DICONV_INCLUDE_DIR="%iconvIF%" -DICONV_LIBRARIES="%iconvLL%" -DSFML_ROOT="%SFMLRF%" -DEXTERN_DIR:PATH="%UserProfile%/Documents/GitHub" ../
mingw32-make -j4
robocopy extern/genieutils/ . libgenieutils.dll /XO /NC /NDL /NJH /NJS
CD ..
PAUSE

CD ..
SET MAIND="%CD:\=/%"
SET COMPD="%CD:\=/%/mingw-w64/mingw32/include"
SET ZLIBL="%CD:\=/%/mingw-w64/mingw32/i686-w64-mingw32/lib/libz.a"
SET ICONL="%CD:\=/%/mingw-w64/mingw32/i686-w64-mingw32/lib/libiconv.a"
SET WXWID="%CD:\=/%/wxWidgets"
SET BOOSD="%CD:\=/%/Boost"
SET BOOSL="%CD:\=/%/Boost/lib/libboost_iostreams-mgw81-mt-d-x32-1_71.dll.a"
SET SFMLD="%CD:\=/%/SFML"
CD AGE
IF NOT EXIST Debug/NUL MKDIR Debug
CD Debug
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DwxWidgets_ROOT_DIR:PATH=%WXWID% -DZLIB_INCLUDE_DIR=%COMPD% -DZLIB_LIBRARY=%ZLIBL% -DICONV_INCLUDE_DIR=%COMPD% -DICONV_LIBRARIES=%ICONL% -DBOOST_ROOT=%BOOSD% -DBoost_IOSTREAMS_LIBRARY_DEBUG=%BOOSL% -DSFML_ROOT=%SFMLD% -DEXTERN_DIR:PATH=%MAIND% ../
mingw32-make -j4
robocopy extern/genieutils/ . libgenieutils.dll /XO /NC /NDL /NJH /NJS
CD ..
PAUSE

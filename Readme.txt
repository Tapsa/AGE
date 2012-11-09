To compile you need to download MinGW, wxWidgets, boost, zlib and CMake.

You have to add MinGW to the system path if you move your compiling environment to a new Windows installment.

CMake:
Install normally and select it to update PATH automatically.

Install/extract rest of the stuff into C:/Cpp or other folder which you like.

MinGW:
Just install from the regular exe (mingw-get-inst-20120426.exe).

For now you need to run this from cmd or PowerShell:
mingw-get install mingw32-libiconv

wxWidgets (I have modded version 2.8.12):
Unpack the zip file.
To use my modded tool tips, seek them from AGE 2 sources and replace wxWidgets ones!
In cmd.exe go to \wxWidgets\build\msw
mingw32-make -f makefile.gcc SHARED=0 BUILD=debug clean
mingw32-make -f makefile.gcc SHARED=0 BUILD=debug
mingw32-make -f makefile.gcc SHARED=0 BUILD=release clean
mingw32-make -f makefile.gcc SHARED=0 BUILD=release

zlib:
Unpack the zip file.
In cmd.exe go to \zlib
mingw32-make -f win32/Makefile.gcc
Then copy as follows:
/mingw/bin/zlib1.dll
/mingw/include/zconf.h
/mingw/include/zlib.h
/mingw/lib/libz.a
/mingw/lib/libz.dll.a

Boost:
Unpack the zip file.
In cmd.exe go to \boost_1_50_0\tools\build\v2
bootstrap.bat gcc
Copy b2.exe and bjam.exe to \boost_1_50_0
Run from \boost_1_50_0
b2 toolset=gcc link=static runtime-link=static threading=multi -sNO_COMPRESSION=0 -sZLIB_SOURCE=C:/Cpp/zlib --build-type=complete install
Change zlib folder if it's in another place!!!
Copy Boost folder from C: to C:\Cpp or wherever you want it.

You'll need to download Apre's dat library from here:
https://github.com/apreiml/genieutils
Place it into AGE 2's subfolder named "extern\genieutils"
Update paths in build*.bat files, and then you are ready to go.

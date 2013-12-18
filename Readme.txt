To compile you need to download MinGW, wxWidgets, boost, zlib and CMake.

You have to add MinGW to the system path if you move your compiling environment to a new Windows installment.

CMake 2.8.12.1:
Install normally and select it to update PATH automatically.
Modify FindwxWidgets.cmake to look for 3.0 libs.

Install/extract rest of the stuff into C:/Cpp or another folder which you like.

MinGW-w64 4.8.2:
Download Mingw-builds Windows 64 using SJLJ and threads-posix.

You may (should not) need to run this from cmd or PowerShell:
mingw-get install mingw32-libiconv
You can also download libiconv from here:
http://ftp.gnu.org/pub/gnu/libiconv/
Then install it like this: ???

wxWidgets 3.0.0:
Unpack the zip file.
In cmd.exe go to \wxWidgets\build\msw
mingw32-make -f makefile.gcc clean
mingw32-make -f makefile.gcc BUILD=debug SHARED=0 USE_RIBBON=0
mingw32-make -f makefile.gcc BUILD=release SHARED=0 USE_RIBBON=0
del /s *.o
del /s *.o.d

zlib 1.2.8:
Unpack the zip file.
In cmd.exe go to \zlib
mingw32-make -f win32/Makefile.gcc
del /s *.o
del /s *.exe
Then copy as follows:
/mingw/bin/zlib1.dll
/mingw/include/zconf.h
/mingw/include/zlib.h
/mingw/lib/libz.a
/mingw/lib/libz.dll.a

Boost 1.55.0:
Unpack the zip file.
In cmd.exe go to \boost_1_50_0\tools\build\v2
bootstrap.bat gcc
Copy b2.exe and bjam.exe to \boost_1_50_0
Run from \boost_1_50_0
b2 toolset=gcc link=static runtime-link=static threading=multi -sNO_COMPRESSION=0 -sZLIB_SOURCE=C:/Cpp/zlib --build-type=complete install
Change zlib folder if it's in another place!!!
Copy Boost folder from C: to C:\Cpp or wherever you want it.

You'll need to download Apre's dat library from here:
https://github.com/Tapsa/genieutils
Place it into AGE's subfolder named "extern\genieutils"
Then you'll need to download his DLL library:
https://github.com/Tapsa/pcrio
Place it into genieutils's subfolder named "extern\pcrio"
Update paths in build*.bat files, and then you are ready to go.

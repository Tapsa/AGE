To compile you need to download MinGW, wxWidgets, Boost, and CMake.

CMake 2.8.12.1: (3.2.3 fails to do debug builds with wxWidgets 2.8)
Install normally and select it to update PATH automatically.
You may need to edit version numbers in
\CMake 2.8\share\cmake-2.8\Modules\Find*.cmake
files to find wxWidgets and Boost.

Install/extract rest of the stuff into C:/Cpp or another folder which you like.

Mingw-builds 5.3.0: (includes gdb, libiconf, python, zlib)
Choose posix threads with dwarf exception handling.
After installing MinGW add its bin folder to the system path.

wxWidgets 3.1.0
Unpack the zip file.
In cmd.exe go to \wxWidgets\build\msw
mingw32-make -f makefile.gcc BUILD=debug clean
mingw32-make -f makefile.gcc BUILD=debug SHARED=1 USE_RIBBON=0 CXXFLAGS="-std=gnu++0x"
mingw32-make -f makefile.gcc BUILD=release clean
mingw32-make -f makefile.gcc BUILD=release SHARED=1 USE_RIBBON=0 CXXFLAGS="-std=gnu++0x"
del /s *.o
del /s *.o.d

Boost 1.60.0:
Unpack the zip file.
In cmd.exe go to \boost_1_60_0\tools\build
bootstrap.bat gcc
Copy b2.exe to \boost_1_60_0
Run from \boost_1_60_0
b2 toolset=gcc link=shared runtime-link=shared threading=multi install
You can safely delete boost_1_60_0 folder after build completes.

You'll need to download Apre's DAT library from here:
https://github.com/Tapsa/genieutils
Then you'll need to download his DLL library:
https://github.com/Tapsa/pcrio
Place them into the same folder where AGE's folder is.
Update paths in build*.bat files, and then you are ready to go.

If building shared libs copy necessary DLL files to execution path or to C:\Windows\System32 or add lib paths to system path.
wx: base, core, adv
Boost: iostreams
genieutils (after each change)

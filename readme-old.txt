To compile you need to download MinGW, wxWidgets, Boost, and CMake.
I am using SFML for simultaneous audio playback.
Hopefully it will support MP3 in the year 2018.

CMake 3.9.4
Install normally and select it to update PATH automatically.
You may need to edit version numbers in
CMake\share\cmake-3.9\Modules\Find*.cmake
files to find wxWidgets and Boost.

Install/extract rest of the stuff into C:\Cpp or another folder which you like.

Mingw-builds 7.1.0 (includes gdb, libiconf, python, zlib)
Choose posix threads with dwarf exception handling.
After installing MinGW add its bin folder to the system path.

wxWidgets 3.1.0
Unpack the zip file.
In cmd.exe go to wxWidgets\build\msw
mingw32-make -f makefile.gcc BUILD=debug clean
mingw32-make -f makefile.gcc BUILD=debug SHARED=1
mingw32-make -f makefile.gcc BUILD=release clean
mingw32-make -f makefile.gcc BUILD=release SHARED=1
del /s *.o
del /s *.o.d

Boost 1.65.1
Unpack the zip file.
In cmd.exe go to boost_1_65_1\tools\build
bootstrap.bat gcc
Copy b2.exe to boost_1_65_1
Run from boost_1_65_1
b2 toolset=gcc link=shared runtime-link=shared threading=multi install --with-iostreams
You can safely delete boost_1_65_1 folder after build completes.

SFML 2.0
Easiest way is using cmake-gui.
Choose source and build folders and tick BUILD_SHARED_LIBS.
Set CMAKE_BUILD_TYPE to Debug and generate configuration.
Run mingw32-make on the chosen build folder.
Do the same with CMAKE_BUILD_TYPE set to Release.

You'll need to download Apre's DAT library from here:
https://github.com/Tapsa/genieutils
Then you'll need to download his DLL library:
https://github.com/Tapsa/pcrio
Place them into the same folder where AGE's folder is.
Update paths in build*.bat files, and then you are ready to go.

If building shared libs copy necessary DLL files to execution path or add lib paths to system path.
wx: base, core, adv
Boost: iostreams
genieutils (after each change)

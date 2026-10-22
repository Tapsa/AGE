# Advanced Genie Editor

A program for editing data files of Age of Empires, Age of Empires II, Star Wars: Galactic Battlegrounds, their expansions, upgrades, and mods.

## Building

To compile with MinGW you need to download `wxWidgets`, `Boost`, and `CMake`.
For Visual Studio, you also need to download and build `zlib` and `libiconv`.
`miniaudio` is used for simultaneous audio playback.
`lz4` is used for decompressing some sprites.

### CMake 4.4.4

Install normally and select it to update PATH automatically.
You may need to edit version numbers in
```sh
CMake\share\cmake-4.4\Modules\Find*.cmake
```
files to find `wxWidgets` and `Boost`.

Extract rest of the stuff into a folder of your choice.
For Visual Studio, add the folder as a system variable `%Cpp libs%`,
where you'll put all required headers and built libraries.

### Mingw-builds 8.1.0

Includes `gdb`, `libiconf`, `zlib`.
Choose `posix threads with dwarf exception handling`.
After installing MinGW add its `bin` folder to the system path.

### wxWidgets 3.3.4

- Unpack the zip file.
- Open the commandline and change the working directory to `wxWidgets\build\msw`
- Execute:
    ```sh
    mingw32-make -f makefile.gcc BUILD=debug clean
    mingw32-make -f makefile.gcc BUILD=debug SHARED=1
    mingw32-make -f makefile.gcc BUILD=release clean
    mingw32-make -f makefile.gcc BUILD=release SHARED=1
    del /s *.o
    del /s *.o.d
    ```

For Visual Studio, open the solution for your Visual Studio version or nearest one in `wxWidgets\build\msw` and build all of it using all configurations you're planning to build **Advanced Genie Editor** with.

### zlib 1.3.2

- Unpack the zip file.
- Open the commandline and run these commands in the unpack location:
    ```sh
    cd zlib-1.3.2
    mkdir build64
    mkdir build32
    cmake -G "Visual Studio 17 2022" -A x64 -DZLIB_BUILD_SHARED=OFF -DZLIB_BUILD_STATIC=ON -B build64
    cmake -G "Visual Studio 17 2022" -A Win32 -DZLIB_BUILD_SHARED=OFF -DZLIB_BUILD_STATIC=ON -B build32
    cmake --build build64 --config Debug
    cmake --build build64 --config Release
    cmake --build build32 --config Debug
    cmake --build build32 --config Release
    ```
- Copy `zlib.h` and `zconf.h` to `%Cpp libs%\zlib\include`
- Copy the built libraries to `%Cpp libs%\zlib\lib\x64\Debug` and `%Cpp libs%\zlib\lib\x86\Release` etc.

### Boost 1.88.0

- Unpack the zip file.
- Copy `boost_1_88_0\boost` to `%Cpp libs%\Boost\include`

### miniaudio 0.11.25

- Download the miniaudio.h to `%Cpp libs%\miniaudio`

### lz4 1.10.0

- Unpack the zip file.
- For static linking using Visual Studio, build the liblz4 project, both `Debug` and `Release`.
- Copy the header files from `lib` folder into `%Cpp libs%\lz4`.
- Create folders `Debug` and `Release` inside `%Cpp libs%\lz4` folder.
- Copy the generated `liblz4_static.lib` files from where they were generated, such as `build\VS2017\bin`.

### Final steps

Clone the following projects into same folder where the `AGE` folder is:
- [Genieutils](https://github.com/Tapsa/genieutils)
- [pcrio](https://github.com/Tapsa/pcrio)

MinGW: Update paths in `build*.bat` files, and then you are ready to go.

Visual Studio solution should be buildable now, but you may need to add some libraries to system path, or copy them into build folders.

If building shared libs copy the necessary DLL files to execution path or add the lib paths to system path.
- wx: base, core
- genieutils (after each change)

## License

**GNU GPLv3**; see [LICENSE](LICENSE).

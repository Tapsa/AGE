# Advanced Genie Editor

A program for editing data files of Age of Empires, Age of Empires II, Star Wars: Galactic Battlegrounds, their expansions, upgrades, and mods.

## Building

To compile with MinGW you need to download `wxWidgets`, `Boost`, and `CMake`.

For Visual Studio, you also need to download and build a compatible version of `libiconv`.

`SFML` is used for simultaneous audio playback.

`lz4` is used for decompressing some sprites.

### CMake 3.29.2

Install normally and select it to update PATH automatically.
You may need to edit version numbers in

```sh
\CMake\share\cmake-3.29\Modules\Find*.cmake
```

files to find `wxWidgets` and `Boost`.

Extract rest of the stuff into a folder of your choice.

For Visual Studio, add a folder as a system variable `%Cpp libs%`,
where you'll put all required headers and built libraries.

### Mingw-builds 8.1.0

Includes `gdb`, `libiconf`, `zlib`.

Choose `posix threads with dwarf exception handling`.

After installing MinGW add its `bin` folder to the system path.

### wxWidgets 3.2.4

- Unpack the zip file.

- Open the commandline and change the working directory to `\wxWidgets\build\msw`

- Execute:

    ```sh
    mingw32-make -f makefile.gcc BUILD=debug clean

    mingw32-make -f makefile.gcc BUILD=debug SHARED=1

    mingw32-make -f makefile.gcc BUILD=release clean

    mingw32-make -f makefile.gcc BUILD=release SHARED=1

    del /s *.o

    del /s *.o.d
    ```

For Visual Studio, open the solution for your Visual Studio version or nearest one in `\wxWidgets\build\msw` and build all of it using all configurations you're planning to build **Advanced Genie Editor** with.

### Boost 1.85.0

- Unpack the zip file.

- Open the commandline and change the working directory to `\boost_1_85_0\tools\build`

- Run `bootstrap.bat`

- Copy `b2.exe` to `\boost_1_85_0`

- Run from `\boost_1_85_0`:

    ```sh
    b2 toolset=gcc link=shared runtime-link=shared threading=multi --with-iostreams
    
    # For Visual Studio, zlib needs to be built too.
    
    b2 toolset=msvc link=static runtime-link=shared threading=multi --with-iostreams -s ZLIB_SOURCE=".\tools\boost_install\test\iostreams\zlib-1.2.11" -s ZLIB_INCLUDE=".\tools\boost_install\test\iostreams\zlib-1.2.11"
    ```

You can safely delete the `boost_1_85_0` folder after build completes.

Visual Studio may require appending `lib` to name of some generated libraries.

### SFML 2.6.1

- Unpack the zip file.

- Use the `cmake-gui` and browse the `SFML` source folder.

- Configure and ensure both `Debug` and `MinSizeRel` CMAKE_CONFIGURATION_TYPES are present.

- Run from `\SFML`

    ```sh
    mingw32-make install
    ```

- Copy `FindSFML.cmake` to `\CMake\share\cmake-3.15\Modules`

### lz4

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

If building shared libs copy necessary DLL files to execution path or add lib paths to system path.

- wx: base, core

- Boost: iostreams

- genieutils (after each change)

## License

**GNU GPLv3**; see [LICENSE](LICENSE).

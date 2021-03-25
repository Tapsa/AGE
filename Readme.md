# Advanced Genie Editor

A program for editing data files of Age of Empires, Age of Empires II, Star Wars: Galactic Battlegrounds, their expansions, upgrades, and mods.

## Installation

__Disclaimer:__ The repository owner is not collaborating with Scoop and updates can be manually downloaded from [aok.heavengames' Blacksmith](https://aok.heavengames.com/blacksmith/showfile.php?fileid=11002).

You can install and keep **Advanced Genie Editor** up-to-date with [scoop](https://scoop.sh/). If you have scoop installed add the `games` bucket with:

```sh
scoop bucket add games
```

and install AGE with

```sh
scoop install advanced-genie-editor
```

## Building

To compile with MinGW you need to download `wxWidgets`, `Boost`, and `CMake`.

`SFML` is used for simultaneous audio playback.

Hopefully it will support MP3 in some year.

For Visual Studio, you also need to download and build a compatible version of `libiconv`.

### CMake 3.15.5

Install normally and select it to update PATH automatically.
You may need to edit version numbers in

```sh
\CMake\share\cmake-3.15\Modules\Find*.cmake
```

files to find `wxWidgets` and `Boost`.

Extract rest of the stuff into a folder of your choice.

For Visual Studio, add a folder as a system variable `%Cpp libs%`,
where you'll put all required headers and built libraries.

### Mingw-builds 8.1.0

It includes `gdb`, `libiconf`, `zlib`.

Choose `posix threads with dwarf exception handling`.

After installing MinGW add its `bin` folder to the system path.

### wxWidgets 3.1.4

- Unpack the zip file.

- Open the commandline and change the working directory `\wxWidgets\build\msw`

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

### Boost 1.75.0

- Unpack the zip file.

- Open the commandline and change the working directory to `\boost_1_75_0\tools\build`

- Run `bootstrap.bat gcc`

- Copy `b2.exe` to `\boost_1_75_0`

- Run from `\boost_1_75_0`:

    ```sh
    b2 toolset=gcc link=shared
    
    runtime-link=shared threading=multi install --with-iostreams
    
    # For Visual Studio, zlib needs to be built too.
    
    b2 toolset=msvc link=static runtime-link=static threading=multi install --with-iostreams -s ZLIB_SOURCE=".\tools\boost_install\test\iostreams\zlib-1.2.11" -s ZLIB_INCLUDE=".\tools\boost_install\test\iostreams\zlib-1.2.11"
    ```

You can safely delete the `boost_1_75_0` folder after build completes.

Visual Studio may require appending `lib` to name of some generated libraries.

### SFML 2.5.1

- Unpack the zip file.

- Use the `cmake-gui` and browse the `SFML` source folder.

- Configure and then generate both `Release` and `Debug` builds.

- Run from `\SFML`

    ```sh
    mingw32-make install
    ```

- Copy `FindSFML.cmake` to `\CMake\share\cmake-3.15\Modules`

Clone the following projects into same folder where the `AGE` folder is:

- [Genieutils](https://github.com/Tapsa/genieutils)

- [pcrio](https://github.com/Tapsa/pcrio)

Update paths in `build*.bat` files, and then you are ready to go.

Visual Studio solution should be buildable now, but you may need to add some libraries to system path, or copy them into build folders.

If building shared libs copy necessary DLL files to execution path or add lib paths to system path.

- wx: base, core

- Boost: iostreams

- genieutils (after each change)

## License

**GNU GPLv3**; see [LICENSE](LICENSE).

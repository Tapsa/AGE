Advanced Genie Editor 3
=======================

![screenshot](/docs/screenshot.jpg)

This is a program for editing data of genie (DAT and DLL) files. It can edit
properties of units, civilizations, technologies, graphics, terrains, sounds,
player colors and some other things.

It supports Age of Empires, Rise of Rome, Age of Kings, The Conquerors (including HD),
Star Wars Galactic Battlegrounds and Clone Campaigns.


Downloads
---------
Official releases and more information is available at
[Age of Kings Heaven](http://aok.heavengames.com/blacksmith/showfile.php?fileid=11002).

Automatic developer builds for Windows are available here:
https://ci.appveyor.com/project/sandsmark/age/build/artifacts


Notes
-----

 - Make your own backups or use the auto-backup feature!
 - Extract to anywhere and run.
 - You may need to run the program as administrator.
 - No help files are included.
 - No mod affects your already saved games, only new games.
 - You may be able to undo changes by going back to the text box and pressing `Ctrl + Z`.


Tips
----

 - You can have multiple search entries separated with "|" letter.
 - Upper search boxes are inclusive and lower ones exclusive.
 - Example: `tower|ship|ram`
 - Use the check boxes to force match all entries.


Dependencies for building
--------
For compiling it yourself you need the following installed:

 * A modern C++ compiler (supporting at least C++17).
 * wxWidgets.
 * SFML (audio module).


Generic build instructions:
--------------------------
Clone with recursive submodules and standard cmake:

```
git clone --recurse-submodules https://github.com/sandsmark/AGE.git
mkdir build && cd build
cmake .. && make
./AdvancedGenieEditor3
```


Windows build instructions
--------------------------
For installing on Windows, it is probably easiest to use [vcpkg](https://github.com/microsoft/vcpkg) to install wxWidgets and SFML, it is what AppVeyor uses.

The commands AppVeyor runs to build static binaries are:

```
vcpkg update
vcpkg install sfml:x86-windows-static
vcpkg install wxwidgets:x86-windows-static
vcpkg integrate install
git submodule update --init --recursive`
cmake -DENABLE_IPO=True -D CMAKE_CXX_FLAGS_RELEASE:STRING="/MT /O2 /Ob2 /DNDEBUG" -DLINKING_TYPE=static -D CMAKE_C_FLAGS_RELEASE:STRING="/MT /O2 /Ob2 /DNDEBUG" -G "Visual Studio 15 2017" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_TOOLCHAIN_FILE=c:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake .
```


Developers
----------
 * Mikko "Tapsa" P, since 2.0b
 * Armin "Apre" Preiml - genieutils and pcrio, 2.1a to 3.1
 * Estien" StSB77" Nifo, 1.0a to 2.0a
 * Martin "martin" Sandsmark


Credits
-------
 * Ykkrosh - GeniEd 1 source code
 * Scenario\_t\_c - GeniEd 2 source code
 * Alexandra "Taichi San", DarkRain654 - data file research
 * DiGiT, JustTesting1234, AOHH - genie file structure
 * Cysion, Kris, Sarthos - important help
 * BF\_Tanks - some help
 * Donnieboy, Sarn, chab - tooltip texts
 * gagman - new icon

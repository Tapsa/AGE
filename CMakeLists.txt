if(${CMAKE_VERSION} VERSION_LESS "3.9.0")
 cmake_minimum_required(VERSION 3.7)
 message("Please upgrade to cmake 3.9 to get more fancy stuff")
else()
 cmake_minimum_required(VERSION 3.9)
endif()

set (CMAKE_CXX_STANDARD 17)

project(AdvancedGenieEditor3)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

if(MSVC)
    # Otherwise we get thousands of warnings from wxwidgets
    # Why on earth people use wxwidgets is beyond me
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(/wd4018)
endif()

# Find wxWidgets
# In case you didn't know, it is crap, so we need this hack
if(MSVC AND _VCPKG_INSTALLED_DIR)
    include(${CMAKE_SOURCE_DIR}/cmake/vcpkg-wxwidgets.cmake)
else()
    find_package(wxWidgets REQUIRED adv core base)
    include("${wxWidgets_USE_FILE}")
endif()

find_package(SFML 2.4 REQUIRED system audio)

set(GUTILS_TOOLS FALSE)
set(GUTILS_TEST FALSE)

if (ENABLE_SANITIZERS)
    message("Enabling asan and ubsan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
endif()

if (ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_AVAILABLE OUTPUT IPO_ERROR)
    if (IPO_AVAILABLE)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)

        if (CMAKE_COMPILER_IS_GNUCXX)
            message(STATUS "Enabling all link time optimizations")
            add_definitions(-fuse-linker-plugin)
        else()
            message(STATUS "Using IPO for optimizing binary size")
        endif()
    else()
        message(STATUS "IPO/LTO not supported: <${IPO_ERROR}>")
    endif()
else()
    message(STATUS "Not enabling IPO/LTO")
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/genieutils/include/genie/Types.h)
    message(STATUS "Using bundled genieutils")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/genieutils/include/)

    set(GENIEUTILS_STATIC_BUILD True)
    add_subdirectory(extern/genieutils)
endif()

include_directories(
    ${SFML_INCLUDE_DIR}
)

set(AGE_SRC Main.cpp
    AGE_TextControls.cpp
    AGE_CheckBoxes.cpp
    AGE_ComboBoxes.cpp
    AGE_AboutDialog.cpp
    AGE_OpenSave.cpp
    AGE_OpenDialog.cpp
    AGE_SaveDialog.cpp
    SharedComboPopup.cpp

    AGE_Frame/Constructor.cpp
    AGE_Frame/Other.cpp
    AGE_Frame/Civs.cpp
    AGE_Frame/General.cpp
    AGE_Frame/Graphics.cpp
    AGE_Frame/PlayerColors.cpp
    AGE_Frame/Research.cpp
    AGE_Frame/Sounds.cpp
    AGE_Frame/Techs.cpp
    AGE_Frame/TechTrees.cpp
    AGE_Frame/TerrainBorders.cpp
    AGE_Frame/TerrainRestrictions.cpp
    AGE_Frame/Terrains.cpp
    AGE_Frame/UnitLine.cpp
    AGE_Frame/Units.cpp

    Resources.rc
    )

if(WIN32)
    include_directories(extern/genieutils/extern/win-iconv/)

    add_executable(AdvancedGenieEditor3 WIN32 ${AGE_SRC})
    target_link_libraries(AdvancedGenieEditor3 ${wxWidgets_LIBRARIES} genieutils psapi sfml-system sfml-audio)
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wno-sign-compare")
    add_executable(AdvancedGenieEditor3 ${AGE_SRC})
    target_link_libraries(AdvancedGenieEditor3 ${wxWidgets_LIBRARIES} genieutils sfml-system sfml-audio stdc++fs)
endif()

install(TARGETS AdvancedGenieEditor3 DESTINATION bin)

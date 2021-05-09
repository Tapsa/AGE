cmake_minimum_required(VERSION 3.7)

project(AdvancedGenieEditor3)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
set(CMAKE_CXX_FLAGS "-Wall -Wno-sign-compare -Wno-parentheses")
set(BOOST_DATE_TIME_NO_LIB   ON)
#set(Boost_USE_STATIC_LIBS    ON)
#set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_USE_MULTITHREADED  ON)

find_package(Boost 1.55 REQUIRED iostreams)

find_package(wxWidgets REQUIRED core base)
include("${wxWidgets_USE_FILE}")

find_package(SFML 2.4 REQUIRED system audio)

set(GUTILS_TOOLS FALSE)
set(GUTILS_TEST FALSE)

include_directories(
    ${EXTERN_DIR}/genieutils/include
    ${SFML_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS})

add_subdirectory(${EXTERN_DIR}/genieutils extern/genieutils)

set(AGE_SRC Precompile/Common.cpp
    #External includes only
    CustomWidgets.cpp
    DelayedMessageRelay.cpp
    SharedComboPopup.cpp

    #Internal includes in cpp only
    LinkedControl.cpp
    OpenSaveDialog.cpp
    AboutDialog.cpp
    Main.cpp
    CustomTextControls.cpp

    #Internal includes in headers too
    LinkedCheckBox.cpp
    CustomComboBoxes.cpp
    OpenDialog.cpp
    SaveDialog.cpp
    Loaders.cpp
    Sprites.cpp

    AGE_Frame/Civs.cpp
    AGE_Frame/General.cpp
    AGE_Frame/PlayerColors.cpp
    AGE_Frame/Research.cpp
    AGE_Frame/TechTrees.cpp
    AGE_Frame/TerrainBorders.cpp
    AGE_Frame/TerrainRestrictions.cpp
    AGE_Frame/UnitLine.cpp
    AGE_Frame/Units.cpp
    AGE_Frame/Techs.cpp
    AGE_Frame/Graphics.cpp
    AGE_Frame/Sounds.cpp
    AGE_Frame/Terrains.cpp
    AGE_Frame/Other.cpp
    AGE_Frame/Lists.cpp
    AGE_Frame/Animation.cpp
    AGE_Frame/Constructor.cpp

    Resources.rc
    )

find_library(PSAPI psapi)

add_executable(AdvancedGenieEditor3 WIN32 ${AGE_SRC})
target_link_libraries(AdvancedGenieEditor3 ${wxWidgets_LIBRARIES} genieutils ${PSAPI} ${SFML_LIBRARIES})

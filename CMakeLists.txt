cmake_minimum_required(VERSION 3.7) # DO NOT UPGRADE THIS OR YOU WILL LOSE wxWidgets 2.8 DEBUG BUILDS!

set (CMAKE_CXX_STANDARD 17)

project(AdvancedGenieEditor3)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
set(CMAKE_CXX_FLAGS "-Wall -Wno-sign-compare")

find_package(wxWidgets REQUIRED adv core base)
include("${wxWidgets_USE_FILE}")

find_package(SFML 2.4 REQUIRED system audio)

set(GUTILS_TOOLS FALSE)
set(GUTILS_TEST FALSE)

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
    find_library(PSAPI psapi)
    add_executable(AdvancedGenieEditor3 WIN32 ${AGE_SRC})
    target_link_libraries(AdvancedGenieEditor3 ${wxWidgets_LIBRARIES} genieutils ${PSAPI} sfml-system sfml-audio)
else()
    add_executable(AdvancedGenieEditor3 ${AGE_SRC})
    target_link_libraries(AdvancedGenieEditor3 ${wxWidgets_LIBRARIES} genieutils sfml-system sfml-audio)
endif()

install(TARGETS AdvancedGenieEditor3 DESTINATION bin)

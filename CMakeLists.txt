cmake_minimum_required(VERSION 2.6)

project(AdvancedGenieEditor2)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.42 COMPONENTS iostreams REQUIRED)
find_package(wxWidgets COMPONENTS adv core base REQUIRED)

include( "${wxWidgets_USE_FILE}" )

set(GDAT_STATIC TRUE)

include_directories( ${CMAKE_HOME_DIRECTORY}/extern/geniedat/include
  ${Boost_INCLUDE_DIRS})
  
add_subdirectory (extern/geniedat )

set(AGE_SRC Main.cpp
			AGE_AboutDialog.cpp
            AGE_CheckBoxes.cpp
			AGE_ComboBoxes.cpp
			AGE_OpenDialog.cpp
			AGE_SaveDialog.cpp
			AGE_ScrolledWindow.cpp
			AGE_TextControls.cpp
			
			AGE_Frame_cpp/Civs.cpp
			AGE_Frame_cpp/Constructor.cpp
			AGE_Frame_cpp/Graphics.cpp
			AGE_Frame_cpp/Other.cpp
			AGE_Frame_cpp/PlayerColors.cpp
			AGE_Frame_cpp/Research.cpp
			AGE_Frame_cpp/Sounds.cpp
			AGE_Frame_cpp/Techage.cpp
			AGE_Frame_cpp/TerrainRestrictions.cpp
			AGE_Frame_cpp/Terrains.cpp
			AGE_Frame_cpp/Units.cpp
			
			Resources.rc
			)
			
add_executable(AdvancedGenieEditor2 WIN32 ${AGE_SRC})

target_link_libraries(AdvancedGenieEditor2 ${wxWidgets_LIBRARIES} geniedat)
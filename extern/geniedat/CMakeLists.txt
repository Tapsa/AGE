#
# Following variables can be set:
#
# GDAT_TOOLS:BOOL	if true, tools for debugging/testing will be build
# GDAT_STATIC:BOOL	if true, geniedat will be build as static library

cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME geniedat)
project(${PROJECT_NAME})

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.42 COMPONENTS iostreams REQUIRED)
find_package(ZLIB REQUIRED)

# additional compiler flags
add_definitions(-Wall)

include_directories(${Boost_INCLUDE_DIRS} include/)

set(LIB_SRC src/ResearchResourceCost.cpp
            src/Research.cpp 
            src/ResourceCost.cpp
            src/Civ.cpp
            src/TechageEffect.cpp
            src/Techage.cpp
            src/Terrain.cpp
            src/GraphicAttackSound.cpp
            src/GraphicDelta.cpp
            src/Graphic.cpp
            src/SoundItem.cpp
            src/Sound.cpp
            src/PlayerColour.cpp
            src/File.cpp
            src/TerrainPassGraphic.cpp
            src/ISerializable.cpp
            src/TerrainRestriction.cpp

            src/Unit.cpp
            src/UnitCommand.cpp
            src/UnitHeader.cpp
            src/unit/AttackOrArmor.cpp
            src/unit/DamageGraphic.cpp
            src/unit/ResourceStorage.cpp
            src/unit/BuildingAnnex.cpp
            src/unit/DeadFish.cpp 
            src/unit/Bird.cpp
            src/unit/Projectile.cpp
            src/unit/ProjectileOnly.cpp
            src/unit/Creatable.cpp
            src/unit/Building.cpp
           )
            
set(TEST_SRC tools/test/test.cpp)

set(EXTRACT_SRC tools/extract/extract.cpp)

set(BINCOMP_SRC tools/bincompare/bincomp.cpp)

if (GDAT_STATIC)
  add_library(${PROJECT_NAME} STATIC ${LIB_SRC})
else (GDAT_STATIC)
  add_library(${PROJECT_NAME} SHARED ${LIB_SRC})
endif (GDAT_STATIC)

target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${Boost_LIBRARIES})

if (GDAT_TOOLS)
	# tools

	add_executable(test ${TEST_SRC})
	target_link_libraries(test ${PROJECT_NAME})

	add_executable(gextract ${EXTRACT_SRC})
	target_link_libraries(gextract ${PROJECT_NAME})

	add_executable(bincomp ${BINCOMP_SRC})
	target_link_libraries(bincomp ${PROJECT_NAME})
endif (GDAT_TOOLS)

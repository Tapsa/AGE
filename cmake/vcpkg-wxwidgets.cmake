# MIT License
#
# Copyright (c) 2018 Tiit Ülejõe
# Copyright (c) 2019 Martin Sandsmark
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please specify CMAKE_TOOLCHAIN_FILE, for example -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake")
    message(FATAL_ERROR "Please clean CMake cache and start again")
    return()
endif()

if(NOT VCPKG_TARGET_TRIPLET)
    if(NOT LINKING_TYPE)
        message(FATAL_ERROR "Please specify -DLINKING_TYPE=static or -DLINKING_TYPE=dynamic")
        return()
    endif()


    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        if(LINKING_TYPE MATCHES "static")
            set(VCPKG_TARGET_TRIPLET "x64-windows-static")
        else()
            set(VCPKG_TARGET_TRIPLET "x64-windows")
        endif()
    else()
        if(LINKING_TYPE MATCHES "static")
            set(VCPKG_TARGET_TRIPLET "x86-windows-static")
        else()
            set(VCPKG_TARGET_TRIPLET "x86-windows")
        endif()
    endif()
endif(NOT VCPKG_TARGET_TRIPLET)

message(STATUS "VCPKG_TARGET_TRIPLET:${VCPKG_TARGET_TRIPLET}")

if (VCPKG_TARGET_TRIPLET MATCHES "static")
    message(STATUS "Static build")
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
    foreach(CompilerFlag ${CompilerFlags})
      string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
else()
    message(STATUS "Dynamic build")
    add_definitions(-DWXUSINGDLL)
endif()

add_definitions(-D_UNICODE -DUNICODE -DwxUSE_GUI=1 -D__WXMSW__ -DwxUSE_UNICODE=1)
include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    message(STATUS "Debug build")
	add_definitions(-D_DEBUG)
	include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib/mswud)
	set(wxWidgets_LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib)
	set(wxWidgets_LIBRARIES
		${wxWidgets_LIB_DIR}/wxbase31ud_net.lib
		${wxWidgets_LIB_DIR}/wxmsw31ud_core.lib
		${wxWidgets_LIB_DIR}/wxbase31ud.lib
        ${wxWidgets_LIB_DIR}/libpng16d.lib
        ${wxWidgets_LIB_DIR}/zlibd.lib
        comctl32 Rpcrt4
		)
else()
    message("Release build")
	include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib/mswu)
	set(wxWidgets_LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)
	set(wxWidgets_LIBRARIES
		${wxWidgets_LIB_DIR}/wxbase31u_net.lib
		${wxWidgets_LIB_DIR}/wxmsw31u_core.lib
		${wxWidgets_LIB_DIR}/wxbase31u.lib
        ${wxWidgets_LIB_DIR}/libpng16.lib
        ${wxWidgets_LIB_DIR}/zlib.lib
        comctl32 Rpcrt4
		)
endif()

message(STATUS "wxWidgets_LIBRARIES       : ${wxWidgets_LIBRARIES}")

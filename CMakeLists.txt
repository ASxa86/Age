cmake_minimum_required(VERSION 3.7)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/macros.cmake)
include(cmake/GenerateExportHeader.cmake)

project(age)

set(CMAKE_DEBUG_POSTFIX          "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX        "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX     "s" CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Needed for finding dynamic SFML libraries on linux. Windows we can use VCPKG for dynamic libraries.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(AGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${AGE_INCLUDE_DIR})

add_subdirectory(examples)
add_subdirectory(src)
add_subdirectory(tools)

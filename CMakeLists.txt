cmake_minimum_required(VERSION 3.7)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Age)

if(MSVC) 
	add_compile_options(/wd4251) # w4251 - 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
	add_compile_options(/W4)
	add_compile_options(/MP)
	add_compile_options(/WX)
	add_compile_options(/D_SCL_SECURE_NO_WARNINGS)
	add_compile_options(/permissive-)
	add_compile_options(-std:c++17)
elseif(CMAKE_COMPILER_IS_GNUCXX) 
	add_definitions("-Werror")
elseif(CMAKE_COMPILER_IS_GNUCC)
	add_definitions("-Werror")
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_DEBUG_POSTFIX          "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX        "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX     "s" CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

#############################################################
#
#	Find Boost
#
find_package(Boost 1.65)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(benchmark)
add_subdirectory(src)
add_subdirectory(test)

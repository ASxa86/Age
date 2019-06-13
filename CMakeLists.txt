cmake_minimum_required(VERSION 3.7)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Age)

if(MSVC)
	add_compile_options(/wd4251) # w4251 - 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
	add_compile_options(/wd4275) # w4275 - non dll-interface class 'std::runtime_error' used as base for dll-interface class
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

if(UNIX)
	# Needed for finding dynamic SFML libraries on linux. Windows we can use VCPKG for dynamic libraries.
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

#############################################################
#
#	Find Boost
#
find_package(Boost 1.65 COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIR})

option(AGE_ENABLE_BENCHMARKS "Enable building the AGE benchmark suite." OFF)
option(AGE_ENABLE_TESTS "Enable building the AGE test suite." ON)
option(AGE_ENABLE_TOOLS "Enable building the AGE tools." ON)
option(AGE_ENABLE_QT "Enable building the AGE benchmark suite." ON)

if(${AGE_ENABLE_QT})
	###############################################
	#
	#	Find Qt
	#
	find_package(Qt5 CONFIG COMPONENTS Core Gui Widgets)
endif()

add_subdirectory(src)

if(${AGE_ENABLE_BENCHMARKS})
	add_subdirectory(benchmarks)
endif()

if(${AGE_ENABLE_TESTS})
	add_subdirectory(tests)
endif()

if(${AGE_ENABLE_TOOLS})
	add_subdirectory(tools)
endif()

cmake_minimum_required(VERSION 3.7)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/GenerateExportHeader.cmake)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(cmake/project_compile_options.cmake)
include(cmake/project_install_target.cmake)
include(cmake/project_gen_export.cmake)

# Needed for finding dynamic SFML libraries on linux. Windows we can use VCPKG for dynamic libraries.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_DEBUG_POSTFIX          "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX        "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX     "s" CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_ROOT_NAME azule)
project(${PROJECT_ROOT_NAME})

option(BUILD_BENCHMARKS "Enable building the benchmark suite. Require Celero." ON)
option(BUILD_TESTS "Enable building the test suite. Requires GTest." ON)
option(BUILD_WARNINGS_AS_ERRORS "Enable the compiler to treat warnings as errors." ON)
option(BUILD_SHARED_LIBS "Enable building ${PROJECT_NAME} as shared libraries." ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_BENCHMARKS)
	add_subdirectory(benchmarks)
endif()

if(BUILD_TESTS)
	add_subdirectory(tests)
endif()

add_subdirectory(apps)
add_subdirectory(src)

################################################################
#
#	Install setup for configuration and exported targets
#

set(PROJECT_CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ROOT_NAME}-config-version.cmake)
write_basic_package_version_file(${PROJECT_CONFIG_VERSION} VERSION 0.0.0 COMPATIBILITY SameMajorVersion)

# Installs ${project}-config.cmake to <prefix>/share
install(EXPORT ${PROJECT_ROOT_NAME}-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})

# Installs include/ to <prefix>/include
install(DIRECTORY include/${PROJECT_ROOT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Installs ${project}-config-version.cmake to <prefix>/share
install(FILES ${PROJECT_CONFIG_VERSION} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})

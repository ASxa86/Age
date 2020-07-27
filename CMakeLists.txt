cmake_minimum_required(VERSION 3.7)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/macros.cmake)
include(cmake/GenerateExportHeader.cmake)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

project(age)

set(CMAKE_CXX_STANDARD 17)

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

if(AGE_ENABLE_BENCHMARKS)
	add_subdirectory(benchmarks)
endif()

add_subdirectory(examples)
add_subdirectory(src)
add_subdirectory(tools)

################################################################
#
#	Install setup for configuration and exported targets
#

set(AGE_CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
write_basic_package_version_file(${AGE_CONFIG_VERSION} VERSION 0.0.0 COMPATIBILITY SameMajorVersion)

# Installs age-config.cmake to <prefix>/share
install(EXPORT age-config DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})

# Installs include/ to <prefix>/include
install(DIRECTORY include/age DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Installs age-config-version.cmake to <prefix>/share
install(FILES ${AGE_CONFIG_VERSION} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})

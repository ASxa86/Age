set(GTEST_INCLUDE_DIR gtest-1.8.0/googletest/include)
set(GTEST_LIBRARY gtest gtest_main)
include_directories(${GTEST_INCLUDE_DIR})

add_subdirectory(gtest-1.8.0)
add_subdirectory(core)
add_subdirectory(math)

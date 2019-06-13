enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(core)
add_subdirectory(entity)
add_subdirectory(math)
add_subdirectory(physics)

if(${AGE_ENABLE_QT})
	add_subdirectory(qt)
endif()

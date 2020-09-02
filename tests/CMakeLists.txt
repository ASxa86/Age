project(test-azule)

add_executable(${PROJECT_NAME})

include(core/source_list.cmake)
include(entity/source_list.cmake)
include(math/source_list.cmake)
include(physics/source_list.cmake)
include(utilities/source_list.cmake)

target_sources(${PROJECT_NAME} PRIVATE
	${CORE_H_LIST}
	${CORE_SRC_LIST}
	# ${ENTITY_H_LIST}
	# ${ENTITY_SRC_LIST}
	# ${MATH_H_LIST}
	# ${MATH_SRC_LIST}
	# ${PHYSICS_H_LIST}
	# ${PHYSICS_SRC_LIST}
	${UTILITIES_H_LIST}
	${UTILITIES_SRC_LIST}
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	GTest::gtest
	GTest::gtest_main
)

project_install_target()
project_compile_options()

add_subdirectory(qt)

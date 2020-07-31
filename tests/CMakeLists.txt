project(test-azule)

AZULE_ADD_TEST()

include(core/source_list.cmake)
include(entity/source_list.cmake)
include(math/source_list.cmake)
include(physics/source_list.cmake)
include(utilities/source_list.cmake)

target_sources(${PROJECT_NAME} PRIVATE
	${CORE_H_LIST}
	${CORE_SRC_LIST}
	${ENTITY_H_LIST}
	${ENTITY_SRC_LIST}
	${MATH_H_LIST}
	${MATH_SRC_LIST}
	${PHYSICS_H_LIST}
	${PHYSICS_SRC_LIST}
	${UTILITIES_H_LIST}
	${UTILITIES_SRC_LIST}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
)

add_subdirectory(qt)

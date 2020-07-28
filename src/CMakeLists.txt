add_subdirectory(plugins)

project(azule)

include(audio/source_list.cmake)
include(core/source_list.cmake)
include(entity/source_list.cmake)
include(graphics/source_list.cmake)
include(math/source_list.cmake)
include(navigation/source_list.cmake)
include(physics/source_list.cmake)
include(terrain/source_list.cmake)
include(utilities/source_list.cmake)

AZULE_ADD_LIBRARY()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/physics)

target_sources(${PROJECT_NAME} PRIVATE
	${AUDIO_H_LIST}
	${AUDIO_SRC_LIST}
	${CORE_H_LIST}
	${CORE_SRC_LIST}
	${ENTITY_H_LIST}
	${ENTITY_SRC_LIST}
	${GRAPHICS_H_LIST}
	${GRAPHICS_SRC_LIST}
	${MATH_H_LIST}
	${MATH_SRC_LIST}
	${NAVIGATION_H_LIST}
	${NAVIGATION_SRC_LIST}
	${PHYSICS_H_LIST}
	${PHYSICS_SRC_LIST}
	${TERRAIN_H_LIST}
	${TERRAIN_SRC_LIST}
	${UTILITIES_H_LIST}
	${UTILITIES_SRC_LIST}
)

find_package(SFML 2 CONFIG COMPONENTS audio system graphics window)

target_link_libraries(${PROJECT_NAME} PUBLIC
	sfml-audio
	sfml-system
	sfml-graphics
	sfml-window
)

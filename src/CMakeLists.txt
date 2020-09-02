project(azule)

include(audio/source_list.cmake)
include(core/source_list.cmake)
include(entity/source_list.cmake)
include(graphics/source_list.cmake)
include(math/source_list.cmake)
include(navigation/source_list.cmake)
include(physics/source_list.cmake)
include(reflection/source_list.cmake)
include(terrain/source_list.cmake)
include(utilities/source_list.cmake)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/physics)

target_sources(${PROJECT_NAME} PRIVATE
	# ${AUDIO_H_LIST}
	# ${AUDIO_SRC_LIST}
	${CORE_H_LIST}
	${CORE_SRC_LIST}
	# ${ENTITY_H_LIST}
	# ${ENTITY_SRC_LIST}
	# ${GRAPHICS_H_LIST}
	# ${GRAPHICS_SRC_LIST}
	# ${MATH_H_LIST}
	# ${MATH_SRC_LIST}
	# ${NAVIGATION_H_LIST}
	# ${NAVIGATION_SRC_LIST}
	# ${PHYSICS_H_LIST}
	# ${PHYSICS_SRC_LIST}
	# ${TERRAIN_H_LIST}
	# ${TERRAIN_SRC_LIST}
	${REFLECTION_H_LIST}
	${REFLECTION_SRC_LIST}
	${UTILITIES_H_LIST}
	${UTILITIES_SRC_LIST}
	FactoryRegister.cpp
)

find_package(Boost COMPONENTS filesystem)
find_package(SFML 2 CONFIG COMPONENTS audio system graphics window)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Boost::filesystem
	sfml-audio
	sfml-system
	sfml-graphics
	sfml-window
	nlohmann_json
	glm
)

project_gen_export()
project_install_target()
project_compile_options()

add_subdirectory(plugins)
add_subdirectory(qt)

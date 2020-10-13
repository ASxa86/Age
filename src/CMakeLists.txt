project(azule)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/physics)

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/azule/ComponentTransform.h
	${PROJECT_INCLUDE_DIR}/azule/Engine.h
	${PROJECT_INCLUDE_DIR}/azule/Entity.h
	${PROJECT_INCLUDE_DIR}/azule/SystemPhysics.h
	${PROJECT_INCLUDE_DIR}/azule/World.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Engine.cpp
	Entity.cpp
	SystemPhysics.cpp
	World.cpp
)

find_package(Boost COMPONENTS filesystem serialization)
find_package(SFML 2 CONFIG COMPONENTS audio system graphics window)
find_package(unofficial-box2d CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Boost::filesystem
	Boost::serialization
	sfml-audio
	sfml-system
	sfml-graphics
	sfml-window
	unofficial::box2d::box2d
)

project_gen_export()
project_install_target()
project_compile_options()

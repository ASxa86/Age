project(AgePong)

################## TEMPORARY ##################
#
#	Find SFML
#
find_package(SFML 2 COMPONENTS audio)

add_executable(${PROJECT_NAME} "")
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	Pong.h
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	Pong.cpp
)

target_link_libraries(${PROJECT_NAME} AgeGraphics AgePhysics sfml-audio)

project(azule-pong)

find_package(SFML 2 COMPONENTS system graphics window)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER examples
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	PaddleAIComponent.h
	PaddleAISystem.h
	Pong.h
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	PaddleAIComponent.cpp
	PaddleAISystem.cpp
	Pong.cpp
)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		${CMAKE_DL_LIBS}
		GL
	)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-audio
	azule-entity
	azule-graphics
	azule-math
	azule-physics
	sfml-system
	sfml-graphics
	sfml-window
)


AZULE_COMPILE_OPTIONS()
AZULE_WARNINGS_AS_ERRORS()
AZULE_INSTALL()

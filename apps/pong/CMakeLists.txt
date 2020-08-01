project(azule-pong)

find_package(SFML 2 COMPONENTS system graphics window)

add_executable(${PROJECT_NAME})

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
	azule
	sfml-system
	sfml-graphics
	sfml-window
)


project_install_target()
project_compile_options()

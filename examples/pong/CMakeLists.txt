project(age-pong)

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

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-graphics
	age-physics
	age-audio
)

AGE_COMPILE_OPTIONS()
AGE_WARNINGS_AS_ERRORS()
AGE_INSTALL()

project(AgePong)

add_executable(${PROJECT_NAME} "")

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

target_link_libraries(${PROJECT_NAME} AgeGraphics AgePhysics AgeAudio)

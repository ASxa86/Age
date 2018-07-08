project(AgePong)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} PRIVATE
	Pong.h
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	Pong.cpp
)

target_link_libraries(${PROJECT_NAME} AgeGraphics AgePhysics AgeAudio)

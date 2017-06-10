project(AgePong)

################## TEMPORARY ##################
#
#	Find SFML
#
find_package(SFML 2.4 COMPONENTS Audio)
include_directories(${SFML_INCLUDE_DIR})

set(TARGET_H
	Pong.h
	Paddle.h
)

set(TARGET_SRC
	main.cpp
	Paddle.cpp
	Pong.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC} ${TARGET_H})

target_link_libraries(${PROJECT_NAME} AgeGraphics ${SFML_AUDIO_LIBRARY})

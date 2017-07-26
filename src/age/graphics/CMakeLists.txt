project(AgeGraphics)

############################################
#
#	Find SFML
#
find_package(SFML 2.4 COMPONENTS System Graphics Window)
include_directories(${SFML_INCLUDE_DIR})

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	CircleComponent.h
	Command.h
	DrawableComponent.h
	Export.h
	KeyEvent.h
	InputComponent.h
	PlayerInputSystem.h
	RectangleComponent.h
	SpriteComponent.h
	Window.h
)

set(TARGET_SRC
	CircleComponent.cpp
	Command.cpp
	DrawableComponent.cpp
	InputComponent.cpp
	KeyEvent.cpp
	PlayerInputSystem.cpp
	RectangleComponent.cpp
	SpriteComponent.cpp
	Window.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

target_link_libraries(${PROJECT_NAME}
	AgeMath
	${SFML_GRAPHICS_LIBRARY}
	${SFML_SYSTEM_LIBRARY}
	${SFML_WINDOW_LIBRARY}
)

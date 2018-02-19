project(AgeGraphics)

############################################
#
#	Find SFML
#
find_package(SFML 2.4 COMPONENTS System Graphics Window)
include_directories(${SFML_INCLUDE_DIR})

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	DrawableSystem.h
	Export.h
	KeyEvent.h
	InputComponent.h
	PlayerInputSystem.h
	RenderSystem.h
	Window.h
)

set(TARGET_SRC
	DrawableSystem.cpp
	InputComponent.cpp
	KeyEvent.cpp
	PlayerInputSystem.cpp
	RenderSystem.cpp
	Window.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

target_link_libraries(${PROJECT_NAME}
	AgeCore
	AgeEntity
	AgeMath
	AgePhysics
	${SFML_GRAPHICS_LIBRARY}
	${SFML_SYSTEM_LIBRARY}
	${SFML_WINDOW_LIBRARY}
)

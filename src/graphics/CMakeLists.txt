project(age-graphics)

############################################
#
#	Find SFML
#
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS system graphics window)

AGE_ADD_LIBRARY()

set(SFML_INCLUDE_DIR ${SFML_DIR}/../../include)
message(STATUS "inc ${SFML_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/graphics/BoxSelectionComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/DrawableSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/HealthBarSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/KeyEvent.h
	${AGE_INCLUDE_DIR}/age/graphics/InputComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/PlayerInputSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/RenderSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/SpriteComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/TextSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/TileMapComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/TileMapSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	DrawableSystem.cpp
	InputComponent.cpp
	KeyEvent.cpp
	PlayerInputSystem.cpp
	RenderSystem.cpp
	SpriteComponent.cpp
	TextSystem.cpp
	TileMapComponent.cpp
	TileMapSystem.cpp
	Window.cpp
)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		GL
	)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-entity
	age-math
	age-terrain
	sfml-system
	sfml-graphics
	sfml-window
)

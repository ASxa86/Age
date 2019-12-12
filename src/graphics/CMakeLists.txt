project(age-graphics)

############################################
#
#	Find SFML
#
find_package(SFML 2 CONFIG COMPONENTS system graphics window)

AGE_ADD_LIBRARY()

target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

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

target_link_libraries(${PROJECT_NAME}
	age-core
	age-entity
	age-math
	age-terrain
	sfml-system
	sfml-graphics
	sfml-window
)

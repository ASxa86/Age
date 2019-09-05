project(AgeGraphics)

############################################
#
#	Find SFML
#
find_package(SFML 2 COMPONENTS system graphics window)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER age
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	BoxSelectionComponent.h
	DrawableSystem.h
	Export.h
	HealthBarSystem.h
	KeyEvent.h
	InputComponent.h
	PlayerInputSystem.h
	RenderSystem.h
	SpriteComponent.h
	TextSystem.h
	TileMapComponent.h
	TileMapSystem.h
	Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	BoxSelectionComponent.cpp
	DrawableSystem.cpp
	InputComponent.cpp
	HealthBarSystem.cpp
	KeyEvent.cpp
	PlayerInputSystem.cpp
	Plugin.cpp
	RenderSystem.cpp
	SpriteComponent.cpp
	TextSystem.cpp
	TileMapComponent.cpp
	TileMapSystem.cpp
	Window.cpp
)

target_link_libraries(${PROJECT_NAME}
	AgeCore
	AgeEntity
	AgeMath
	AgeTerrain
	sfml-system
	sfml-graphics
	sfml-window
)

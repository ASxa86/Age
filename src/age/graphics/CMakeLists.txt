project(AgeGraphics)

############################################
#
#	Find SFML
#
find_package(SFML 2 COMPONENTS system graphics window)

############################################
#
#	FindPugi
#
find_package(PugiXML)

add_library(${PROJECT_NAME} SHARED "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	DrawableSystem.h
	Export.h
	KeyEvent.h
	InputComponent.h
	PlayerInputSystem.h
	RenderSystem.h
	SpriteComponent.h
	TextSystem.h
	TileMap.h
	TileMapComponent.h
	TileMapSystem.h
	Window.h
)

target_sources(${PROJECT_NAME} PRIVATE
	DrawableSystem.cpp
	InputComponent.cpp
	KeyEvent.cpp
	PlayerInputSystem.cpp
	RenderSystem.cpp
	SpriteComponent.cpp
	TextSystem.cpp
	TileMap.cpp
	TileMapComponent.cpp
	TileMapSystem.cpp
	Window.cpp
)

target_link_libraries(${PROJECT_NAME}
	AgeCore
	AgeEntity
	AgeMath
	sfml-system
	sfml-graphics
	sfml-window
	pugixml
)

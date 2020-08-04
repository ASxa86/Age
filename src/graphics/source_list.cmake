set(GRAPHICS_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/graphics/BoxSelectionComponent.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/DatabaseTexture.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/DrawableComponent.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/InputComponent.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/KeyEvent.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/PlayerInputSystem.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/ProgressBarComponent.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/RenderSystem.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/SpriteComponent.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/TextSystem.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/TileMapComponent.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/TileMapSystem.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/Utilities.h
	${PROJECT_INCLUDE_DIR}/azule/graphics/Window.h
)

set(GRAPHICS_SRC_LIST
	graphics/BoxSelectionComponent.cpp
	graphics/DatabaseTexture.cpp
	graphics/DrawableComponent.cpp
	graphics/InputComponent.cpp
	graphics/KeyEvent.cpp
	graphics/PlayerInputSystem.cpp
	graphics/ProgressBarComponent.cpp
	graphics/RenderSystem.cpp
	graphics/SpriteComponent.cpp
	graphics/TextSystem.cpp
	graphics/TileMapComponent.cpp
	graphics/TileMapSystem.cpp
	graphics/Utilities.cpp
	graphics/Window.cpp
)

if(MSVC)
	source_group("Header Files\\graphics" FILES ${GRAPHICS_H_LIST})
	source_group("Source Files\\graphics" FILES ${GRAPHICS_SRC_LIST})
endif()

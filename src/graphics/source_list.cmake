set(GRAPHICS_H_LIST
	${AZULE_INCLUDE_DIR}/azule/graphics/BoxSelectionComponent.h
	${AZULE_INCLUDE_DIR}/azule/graphics/DatabaseTexture.h
	${AZULE_INCLUDE_DIR}/azule/graphics/DrawableComponent.h
	${AZULE_INCLUDE_DIR}/azule/graphics/InputComponent.h
	${AZULE_INCLUDE_DIR}/azule/graphics/KeyEvent.h
	${AZULE_INCLUDE_DIR}/azule/graphics/PlayerInputSystem.h
	${AZULE_INCLUDE_DIR}/azule/graphics/ProgressBarComponent.h
	${AZULE_INCLUDE_DIR}/azule/graphics/RenderSystem.h
	${AZULE_INCLUDE_DIR}/azule/graphics/SpriteComponent.h
	${AZULE_INCLUDE_DIR}/azule/graphics/TextSystem.h
	${AZULE_INCLUDE_DIR}/azule/graphics/TileMapComponent.h
	${AZULE_INCLUDE_DIR}/azule/graphics/TileMapSystem.h
	${AZULE_INCLUDE_DIR}/azule/graphics/Utilities.h
	${AZULE_INCLUDE_DIR}/azule/graphics/Window.h
)

set(GRAPHICS_SRC_LIST
	graphics/BoxSelectionComponent.cpp
	graphics/DatabaseTexture.cpp
	graphics/DrawableComponent.cpp
	graphics/InputComponent.cpp
	graphics/KeyEvent.cpp
	graphics/PlayerInputSystem.cpp
	graphics/ProgressBarComponent.cpp
	graphics/Reflection.cpp
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

project(azule-graphics)

############################################
#
#	Find SFML
#
find_package(SFML 2 COMPONENTS system graphics window)

AZULE_ADD_LIBRARY()

set(SFML_INCLUDE_DIR ${SFML_DIR}/../../include)
message(STATUS "inc ${SFML_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
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

target_sources(${PROJECT_NAME} PRIVATE
	BoxSelectionComponent.cpp
	DatabaseTexture.cpp
	DrawableComponent.cpp
	InputComponent.cpp
	KeyEvent.cpp
	PlayerInputSystem.cpp
	ProgressBarComponent.cpp
	Reflection.cpp
	RenderSystem.cpp
	SpriteComponent.cpp
	TextSystem.cpp
	TileMapComponent.cpp
	TileMapSystem.cpp
	Utilities.cpp
	Window.cpp
)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		GL
	)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
	azule-core
	azule-entity
	azule-math
	azule-terrain
	azule-utilities
	sfml-system
	sfml-graphics
	sfml-window
)

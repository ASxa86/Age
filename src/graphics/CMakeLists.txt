project(age-graphics)

############################################
#
#	Find SFML
#
find_package(SFML 2 COMPONENTS system graphics window)

AGE_ADD_LIBRARY()

set(SFML_INCLUDE_DIR ${SFML_DIR}/../../include)
message(STATUS "inc ${SFML_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/graphics/InputComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/KeyEvent.h
	${AGE_INCLUDE_DIR}/age/graphics/PlayerInputSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/RenderSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/SpriteComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/TextSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/TileMapComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/TileMapSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/Window.h
	${AGE_INCLUDE_DIR}/age/graphics/BoxSelectionComponent.h
	${AGE_INCLUDE_DIR}/age/graphics/DrawableSystem.h
	${AGE_INCLUDE_DIR}/age/graphics/HealthBarSystem.h
)

target_sources(${PROJECT_NAME} PRIVATE
	RenderSystem.cpp
	SpriteComponent.cpp
	TextSystem.cpp
	TileMapComponent.cpp
	TileMapSystem.cpp
	Window.cpp
	BoxSelectionComponent.cpp
	DrawableSystem.cpp
	HealthBarSystem.cpp
	InputComponent.cpp
	KeyEvent.cpp
	PlayerInputSystem.cpp
	Reflection.cpp
)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		GL
	)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
	age-core
	age-entity
	age-math
	age-terrain
	age-utilities
	sfml-system
	sfml-graphics
	sfml-window
)

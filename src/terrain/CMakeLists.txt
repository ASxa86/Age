project(age-terrain)

AGE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/terrain/TileMap.h
	${AGE_INCLUDE_DIR}/age/terrain/TileMapLayer.h
	${AGE_INCLUDE_DIR}/age/terrain/TileSet.h
	${AGE_INCLUDE_DIR}/age/terrain/TileSource.h
)

target_sources(${PROJECT_NAME} PRIVATE
	TileMap.cpp
	TileMapLayer.cpp
	TileSet.cpp
	TileSource.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-math
)

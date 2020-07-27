project(azule-terrain)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/terrain/TileMap.h
	${AZULE_INCLUDE_DIR}/azule/terrain/TileMapLayer.h
	${AZULE_INCLUDE_DIR}/azule/terrain/TileSet.h
	${AZULE_INCLUDE_DIR}/azule/terrain/TileSource.h
)

target_sources(${PROJECT_NAME} PRIVATE
	TileMap.cpp
	TileMapLayer.cpp
	TileSet.cpp
	TileSource.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core
	azule-math
)

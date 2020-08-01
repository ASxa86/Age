set(TERRAIN_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/terrain/TileMap.h
	${PROJECT_INCLUDE_DIR}/azule/terrain/TileMapLayer.h
	${PROJECT_INCLUDE_DIR}/azule/terrain/TileSet.h
	${PROJECT_INCLUDE_DIR}/azule/terrain/TileSource.h
)

set(TERRAIN_SRC_LIST
	terrain/TileMap.cpp
	terrain/TileMapLayer.cpp
	terrain/TileSet.cpp
	terrain/TileSource.cpp
)

if(MSVC)
	source_group("Header Files\\terrain" FILES ${TERRAIN_H_LIST})
	source_group("Source Files\\terrain" FILES ${TERRAIN_SRC_LIST})
endif()

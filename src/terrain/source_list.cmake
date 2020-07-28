set(TERRAIN_H_LIST
	${AZULE_INCLUDE_DIR}/azule/terrain/TileMap.h
	${AZULE_INCLUDE_DIR}/azule/terrain/TileMapLayer.h
	${AZULE_INCLUDE_DIR}/azule/terrain/TileSet.h
	${AZULE_INCLUDE_DIR}/azule/terrain/TileSource.h
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

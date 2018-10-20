project(AgeTerrain)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	Export.h
	TileMap.h
	TileMapLayer.h
	TileSet.h
	TileSource.h
)

target_sources(${PROJECT_NAME} PRIVATE
	TileMap.cpp
	TileMapLayer.cpp
	TileSet.cpp
	TileSource.cpp
)

target_link_libraries(${PROJECT_NAME} AgeCore AgeMath)

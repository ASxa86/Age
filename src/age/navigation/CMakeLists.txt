project(AgeNavigation)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	Export.h
	WaypointComponent.h
	WaypointSystem.h
)

target_sources(${PROJECT_NAME} PRIVATE
	WaypointSystem.cpp
)

target_link_libraries(${PROJECT_NAME} AgeCore AgeMath AgePhysics)

project(azule-navigation)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/navigation/WaypointComponent.h
	${AZULE_INCLUDE_DIR}/azule/navigation/WaypointSystem.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Reflection.cpp
	WaypointComponent.cpp
	WaypointSystem.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core
	azule-entity
	azule-math
	azule-physics
	azule-utilities
)

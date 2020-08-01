set(NAVIGATION_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/navigation/WaypointComponent.h
	${PROJECT_INCLUDE_DIR}/azule/navigation/WaypointSystem.h
)

set(NAVIGATION_SRC_LIST
	navigation/Reflection.cpp
	navigation/WaypointComponent.cpp
	navigation/WaypointSystem.cpp
)

if(MSVC)
	source_group("Header Files\\navigation" FILES ${NAVIGATION_H_LIST})
	source_group("Source Files\\navigation" FILES ${NAVIGATION_SRC_LIST})
endif()

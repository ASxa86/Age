project(age-navigation)

AGE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/navigation/WaypointComponent.h
	${AGE_INCLUDE_DIR}/age/navigation/WaypointSystem.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ComponentFactoryRegister.cpp
	WaypointComponent.cpp
	WaypointSystem.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-entity
	age-math
	age-physics
)

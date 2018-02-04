project(AgePhysics)

add_definitions(-D${PROJECT_NAME}_Export)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TARGET_H
	BoxCollisionComponent.h
	CircleCollisionComponent.h
	CollisionEvent.h
	Export.h
	KinematicComponent.h
	PhysicsSystem.h
)

set(TARGET_SRC
	BoxCollisionComponent.cpp
	CircleCollisionComponent.cpp
	CollisionEvent.cpp
	KinematicComponent.cpp
	PhysicsSystem.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

target_link_libraries(${PROJECT_NAME}
	AgeEntity
	AgeMath
)

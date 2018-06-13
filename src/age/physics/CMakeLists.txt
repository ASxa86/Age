project(AgePhysics)

add_library(${PROJECT_NAME} SHARED "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	BoxCollisionComponent.h
	CircleCollisionComponent.h
	CollisionEvent.h
	Export.h
	KinematicComponent.h
	PhysicsSystem.h
)

target_sources(${PROJECT_NAME} PRIVATE
	BoxCollisionComponent.cpp
	CircleCollisionComponent.cpp
	CollisionEvent.cpp
	KinematicComponent.cpp
	PhysicsSystem.cpp
)

target_link_libraries(${PROJECT_NAME}
	AgeEntity
	AgeMath
)

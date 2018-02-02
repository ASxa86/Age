project(AgePhysics)

add_definitions(-D${PROJECT_NAME}_Export)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TARGET_H
	BoxCollisionComponent.h
	CircleCollisionComponent.h
	Export.h
	KinematicComponent.h
	PhysicsSystem.h
)

set(TARGET_SRC
	BoxCollisionComponent.cpp
	CircleCollisionComponent.cpp
	KinematicComponent.cpp
	PhysicsSystem.cpp
)

set(BOX2D_H
	${TARGET_H_BOX2D}
	${TARGET_H_BOX2D_COLLISION}
	${TARGET_H_BOX2D_COMMON}
	${TARGET_H_BOX2D_DYNAMICS}
	${TARGET_H_BOX2D_ROPE}
)

set(BOX2D_SRC
	${TARGET_SRC_BOX2D_COLLISION}
	${TARGET_SRC_BOX2D_COMMON}
	${TARGET_SRC_BOX2D_DYNAMICS}
	${TARGET_SRC_BOX2D_ROPE}
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${BOX2D_SRC} ${TARGET_H} ${BOX2D_H})

target_link_libraries(${PROJECT_NAME}
	AgeEntity
	AgeMath
)

if(MSVC)
	source_group("Header Files\\Box2D" FILES ${TARGET_H_BOX2D})
	source_group("Header Files\\Box2D\\Collision" FILES ${TARGET_H_BOX2D_COLLISION})
	source_group("Header Files\\Box2D\\Common" FILES ${TARGET_H_BOX2D_COMMON})
	source_group("Header Files\\Box2D\\Dynamics" FILES ${TARGET_H_BOX2D_DYNAMICS})
	source_group("Header Files\\Box2D\\Rope" FILES ${TARGET_H_BOX2D_ROPE})
	source_group("Source Files\\Box2D\\Collision" FILES ${TARGET_SRC_BOX2D_COLLISION})
	source_group("Source Files\\Box2D\\Common" FILES ${TARGET_SRC_BOX2D_COMMON})
	source_group("Source Files\\Box2D\\Dynamics" FILES ${TARGET_SRC_BOX2D_DYNAMICS})
	source_group("Source Files\\Box2D\\Rope" FILES ${TARGET_SRC_BOX2D_ROPE})	
endif()
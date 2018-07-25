project(AgePhysics)

###############################################
#
#	Find Box2D
#
# find_package(unofficial-box2d CONFIG REQUIRED)

set(TARGET_H_BOX2D
	Box2D/Box2D.h
)

set(TARGET_H_BOX2D_COLLISION
	Box2D/Collision/b2DynamicTree.h
	Box2D/Collision/b2TimeOfImpact.h
	Box2D/Collision/b2BroadPhase.h
	Box2D/Collision/b2Collision.h
	Box2D/Collision/b2Distance.h
	Box2D/Collision/Shapes/b2Shape.h
	Box2D/Collision/Shapes/b2ChainShape.h
	Box2D/Collision/Shapes/b2CircleShape.h
	Box2D/Collision/Shapes/b2EdgeShape.h
	Box2D/Collision/Shapes/b2PolygonShape.h
)

set(TARGET_H_BOX2D_COMMON
	Box2D/Common/b2Timer.h
	Box2D/Common/b2BlockAllocator.h
	Box2D/Common/b2Draw.h
	Box2D/Common/b2GrowableStack.h
	Box2D/Common/b2Math.h
	Box2D/Common/b2Settings.h
	Box2D/Common/b2StackAllocator.h
)

set(TARGET_H_BOX2D_DYNAMICS
	Box2D/Dynamics/b2Body.h
	Box2D/Dynamics/b2ContactManager.h
	Box2D/Dynamics/b2Fixture.h
	Box2D/Dynamics/b2Island.h
	Box2D/Dynamics/b2TimeStep.h
	Box2D/Dynamics/b2World.h
	Box2D/Dynamics/b2WorldCallbacks.h
	Box2D/Dynamics/Joints/b2WeldJoint.h
	Box2D/Dynamics/Joints/b2WheelJoint.h
	Box2D/Dynamics/Joints/b2DistanceJoint.h
	Box2D/Dynamics/Joints/b2FrictionJoint.h
	Box2D/Dynamics/Joints/b2GearJoint.h
	Box2D/Dynamics/Joints/b2Joint.h
	Box2D/Dynamics/Joints/b2MotorJoint.h
	Box2D/Dynamics/Joints/b2MouseJoint.h
	Box2D/Dynamics/Joints/b2PrismaticJoint.h
	Box2D/Dynamics/Joints/b2PulleyJoint.h
	Box2D/Dynamics/Joints/b2RevoluteJoint.h
	Box2D/Dynamics/Joints/b2RopeJoint.h
	Box2D/Dynamics/Contacts/b2PolygonContact.h
	Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h
	Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h
	Box2D/Dynamics/Contacts/b2CircleContact.h
	Box2D/Dynamics/Contacts/b2Contact.h
	Box2D/Dynamics/Contacts/b2ContactSolver.h
	Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h
	Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h
	Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h
)

set(TARGET_H_BOX2D_ROPE
	Box2D/Rope/b2Rope.h
)

set(TARGET_SRC_BOX2D_COLLISION
	Box2D/Collision/b2TimeOfImpact.cpp
	Box2D/Collision/b2BroadPhase.cpp
	Box2D/Collision/b2CollideCircle.cpp
	Box2D/Collision/b2CollideEdge.cpp
	Box2D/Collision/b2CollidePolygon.cpp
	Box2D/Collision/b2Collision.cpp
	Box2D/Collision/b2Distance.cpp
	Box2D/Collision/b2DynamicTree.cpp
	Box2D/Collision/Shapes/b2PolygonShape.cpp
	Box2D/Collision/Shapes/b2ChainShape.cpp
	Box2D/Collision/Shapes/b2CircleShape.cpp
	Box2D/Collision/Shapes/b2EdgeShape.cpp
)

set(TARGET_SRC_BOX2D_COMMON
	Box2D/Common/b2BlockAllocator.cpp
	Box2D/Common/b2Draw.cpp
	Box2D/Common/b2Math.cpp
	Box2D/Common/b2Settings.cpp
	Box2D/Common/b2StackAllocator.cpp
	Box2D/Common/b2Timer.cpp
)

set(TARGET_SRC_BOX2D_DYNAMICS
	Box2D/Dynamics/b2Body.cpp
	Box2D/Dynamics/b2ContactManager.cpp
	Box2D/Dynamics/b2Fixture.cpp
	Box2D/Dynamics/b2Island.cpp
	Box2D/Dynamics/b2World.cpp
	Box2D/Dynamics/b2WorldCallbacks.cpp
	Box2D/Dynamics/Joints/b2FrictionJoint.cpp
	Box2D/Dynamics/Joints/b2GearJoint.cpp
	Box2D/Dynamics/Joints/b2Joint.cpp
	Box2D/Dynamics/Joints/b2MotorJoint.cpp
	Box2D/Dynamics/Joints/b2MouseJoint.cpp
	Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
	Box2D/Dynamics/Joints/b2PulleyJoint.cpp
	Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
	Box2D/Dynamics/Joints/b2RopeJoint.cpp
	Box2D/Dynamics/Joints/b2WeldJoint.cpp
	Box2D/Dynamics/Joints/b2WheelJoint.cpp
	Box2D/Dynamics/Joints/b2DistanceJoint.cpp
	Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
	Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
	Box2D/Dynamics/Contacts/b2CircleContact.cpp
	Box2D/Dynamics/Contacts/b2Contact.cpp
	Box2D/Dynamics/Contacts/b2ContactSolver.cpp
	Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
	Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
	Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
	Box2D/Dynamics/Contacts/b2PolygonContact.cpp
)

set(TARGET_SRC_BOX2D_ROPE
	Box2D/Rope/b2Rope.cpp
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

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(${PROJECT_NAME} SHARED ${BOX2D_SRC} ${BOX2D_H})
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
	# unofficial::box2d::Box2D
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

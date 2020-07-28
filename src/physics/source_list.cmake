set(TARGET_H_BOX2D
	physics/Box2D/Box2D.h
)

set(TARGET_H_BOX2D_COLLISION
	physics/Box2D/Collision/b2DynamicTree.h
	physics/Box2D/Collision/b2TimeOfImpact.h
	physics/Box2D/Collision/b2BroadPhase.h
	physics/Box2D/Collision/b2Collision.h
	physics/Box2D/Collision/b2Distance.h
	physics/Box2D/Collision/Shapes/b2Shape.h
	physics/Box2D/Collision/Shapes/b2ChainShape.h
	physics/Box2D/Collision/Shapes/b2CircleShape.h
	physics/Box2D/Collision/Shapes/b2EdgeShape.h
	physics/Box2D/Collision/Shapes/b2PolygonShape.h
)

set(TARGET_H_BOX2D_COMMON
	physics/Box2D/Common/b2Timer.h
	physics/Box2D/Common/b2BlockAllocator.h
	physics/Box2D/Common/b2Draw.h
	physics/Box2D/Common/b2GrowableStack.h
	physics/Box2D/Common/b2Math.h
	physics/Box2D/Common/b2Settings.h
	physics/Box2D/Common/b2StackAllocator.h
)

set(TARGET_H_BOX2D_DYNAMICS
	physics/Box2D/Dynamics/b2Body.h
	physics/Box2D/Dynamics/b2ContactManager.h
	physics/Box2D/Dynamics/b2Fixture.h
	physics/Box2D/Dynamics/b2Island.h
	physics/Box2D/Dynamics/b2TimeStep.h
	physics/Box2D/Dynamics/b2World.h
	physics/Box2D/Dynamics/b2WorldCallbacks.h
	physics/Box2D/Dynamics/Joints/b2WeldJoint.h
	physics/Box2D/Dynamics/Joints/b2WheelJoint.h
	physics/Box2D/Dynamics/Joints/b2DistanceJoint.h
	physics/Box2D/Dynamics/Joints/b2FrictionJoint.h
	physics/Box2D/Dynamics/Joints/b2GearJoint.h
	physics/Box2D/Dynamics/Joints/b2Joint.h
	physics/Box2D/Dynamics/Joints/b2MotorJoint.h
	physics/Box2D/Dynamics/Joints/b2MouseJoint.h
	physics/Box2D/Dynamics/Joints/b2PrismaticJoint.h
	physics/Box2D/Dynamics/Joints/b2PulleyJoint.h
	physics/Box2D/Dynamics/Joints/b2RevoluteJoint.h
	physics/Box2D/Dynamics/Joints/b2RopeJoint.h
	physics/Box2D/Dynamics/Contacts/b2PolygonContact.h
	physics/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h
	physics/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h
	physics/Box2D/Dynamics/Contacts/b2CircleContact.h
	physics/Box2D/Dynamics/Contacts/b2Contact.h
	physics/Box2D/Dynamics/Contacts/b2ContactSolver.h
	physics/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h
	physics/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h
	physics/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h
)

set(TARGET_H_BOX2D_ROPE
	physics/Box2D/Rope/b2Rope.h
)

set(TARGET_SRC_BOX2D_COLLISION
	physics/Box2D/Collision/b2TimeOfImpact.cpp
	physics/Box2D/Collision/b2BroadPhase.cpp
	physics/Box2D/Collision/b2CollideCircle.cpp
	physics/Box2D/Collision/b2CollideEdge.cpp
	physics/Box2D/Collision/b2CollidePolygon.cpp
	physics/Box2D/Collision/b2Collision.cpp
	physics/Box2D/Collision/b2Distance.cpp
	physics/Box2D/Collision/b2DynamicTree.cpp
	physics/Box2D/Collision/Shapes/b2PolygonShape.cpp
	physics/Box2D/Collision/Shapes/b2ChainShape.cpp
	physics/Box2D/Collision/Shapes/b2CircleShape.cpp
	physics/Box2D/Collision/Shapes/b2EdgeShape.cpp
)

set(TARGET_SRC_BOX2D_COMMON
	physics/Box2D/Common/b2BlockAllocator.cpp
	physics/Box2D/Common/b2Draw.cpp
	physics/Box2D/Common/b2Math.cpp
	physics/Box2D/Common/b2Settings.cpp
	physics/Box2D/Common/b2StackAllocator.cpp
	physics/Box2D/Common/b2Timer.cpp
)

set(TARGET_SRC_BOX2D_DYNAMICS
	physics/Box2D/Dynamics/b2Body.cpp
	physics/Box2D/Dynamics/b2ContactManager.cpp
	physics/Box2D/Dynamics/b2Fixture.cpp
	physics/Box2D/Dynamics/b2Island.cpp
	physics/Box2D/Dynamics/b2World.cpp
	physics/Box2D/Dynamics/b2WorldCallbacks.cpp
	physics/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
	physics/Box2D/Dynamics/Joints/b2GearJoint.cpp
	physics/Box2D/Dynamics/Joints/b2Joint.cpp
	physics/Box2D/Dynamics/Joints/b2MotorJoint.cpp
	physics/Box2D/Dynamics/Joints/b2MouseJoint.cpp
	physics/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
	physics/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
	physics/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
	physics/Box2D/Dynamics/Joints/b2RopeJoint.cpp
	physics/Box2D/Dynamics/Joints/b2WeldJoint.cpp
	physics/Box2D/Dynamics/Joints/b2WheelJoint.cpp
	physics/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
	physics/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
	physics/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
	physics/Box2D/Dynamics/Contacts/b2CircleContact.cpp
	physics/Box2D/Dynamics/Contacts/b2Contact.cpp
	physics/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
	physics/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
	physics/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
	physics/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
	physics/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
)

set(TARGET_SRC_BOX2D_ROPE
	physics/Box2D/Rope/b2Rope.cpp
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

set(PHYSICS_H_LIST
	${AZULE_INCLUDE_DIR}/azule/physics/BoxCollisionComponent.h
	${AZULE_INCLUDE_DIR}/azule/physics/CircleCollisionComponent.h
	${AZULE_INCLUDE_DIR}/azule/physics/CollisionEvent.h
	${AZULE_INCLUDE_DIR}/azule/physics/CollisionComponent.h
	${AZULE_INCLUDE_DIR}/azule/physics/EdgeCollisionComponent.h
	${AZULE_INCLUDE_DIR}/azule/physics/KinematicComponent.h
	${AZULE_INCLUDE_DIR}/azule/physics/PhysicsSystem.h
	${AZULE_INCLUDE_DIR}/azule/physics/PhysicsRenderSystem.h
	${BOX2D_H}
)

set(PHYSICS_SRC_LIST
	physics/CircleCollisionComponent.cpp
	physics/CollisionComponent.cpp
	physics/CollisionEvent.cpp
	physics/KinematicComponent.cpp
	physics/PhysicsSystem.cpp
	physics/PhysicsRenderSystem.cpp
	physics/Reflection.cpp
	${BOX2D_SRC}
)

if(MSVC)
	source_group("Header Files\\physics" FILES ${PHYSICS_H_LIST})
	source_group("Source Files\\physics" FILES ${PHYSICS_SRC_LIST})

	source_group("Header Files\\physics\\Box2D" FILES ${TARGET_H_BOX2D})
	source_group("Header Files\\physics\\Box2D\\Collision" FILES ${TARGET_H_BOX2D_COLLISION})
	source_group("Header Files\\physics\\Box2D\\Common" FILES ${TARGET_H_BOX2D_COMMON})
	source_group("Header Files\\physics\\Box2D\\Dynamics" FILES ${TARGET_H_BOX2D_DYNAMICS})
	source_group("Header Files\\physics\\Box2D\\Rope" FILES ${TARGET_H_BOX2D_ROPE})
	source_group("Source Files\\physics\\Box2D\\Collision" FILES ${TARGET_SRC_BOX2D_COLLISION})
	source_group("Source Files\\physics\\Box2D\\Common" FILES ${TARGET_SRC_BOX2D_COMMON})
	source_group("Source Files\\physics\\Box2D\\Dynamics" FILES ${TARGET_SRC_BOX2D_DYNAMICS})
	source_group("Source Files\\physics\\Box2D\\Rope" FILES ${TARGET_SRC_BOX2D_ROPE})
endif()

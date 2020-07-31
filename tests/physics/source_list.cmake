set(PHYSICS_H_LIST
)

set(PHYSICS_SRC_LIST
	physics/PhysicsSystem.test.cpp
)

if(MSVC)
	source_group("Header Files\\physics" FILES ${PHYSICS_H_LIST})
	source_group("Source Files\\physics" FILES ${PHYSICS_SRC_LIST})
endif()

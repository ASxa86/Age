project(azule-entity)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/entity/Animation.h
	${AZULE_INCLUDE_DIR}/azule/entity/AnimationChannel.h
	${AZULE_INCLUDE_DIR}/azule/entity/AnimationComponent.h
	${AZULE_INCLUDE_DIR}/azule/entity/AnimationSystem.h
	${AZULE_INCLUDE_DIR}/azule/entity/CloneSystem.h
	${AZULE_INCLUDE_DIR}/azule/entity/Component.h
	${AZULE_INCLUDE_DIR}/azule/entity/Entity.h
	${AZULE_INCLUDE_DIR}/azule/entity/EntityDatabase.h
	${AZULE_INCLUDE_DIR}/azule/entity/EntityEvent.h
	${AZULE_INCLUDE_DIR}/azule/entity/SelectionComponent.h
	${AZULE_INCLUDE_DIR}/azule/entity/System.h
	${AZULE_INCLUDE_DIR}/azule/entity/TransformComponent.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Animation.cpp
	AnimationChannel.cpp
	AnimationComponent.cpp
	AnimationSystem.cpp
	CloneSystem.cpp
	Component.cpp
	Entity.cpp
	EntityDatabase.cpp
	EntityEvent.cpp
	Reflection.cpp
	SelectionComponent.cpp
	System.cpp
	TransformComponent.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core
	azule-math
	azule-utilities
)

find_package(EnTT CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	EnTT::EnTT
)

AZULE_INCLUDE_BOOST()

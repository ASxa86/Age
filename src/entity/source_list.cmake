set(ENTITY_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/entity/Animation.h
	${PROJECT_INCLUDE_DIR}/azule/entity/AnimationChannel.h
	${PROJECT_INCLUDE_DIR}/azule/entity/AnimationComponent.h
	${PROJECT_INCLUDE_DIR}/azule/entity/AnimationSystem.h
	${PROJECT_INCLUDE_DIR}/azule/entity/CloneSystem.h
	${PROJECT_INCLUDE_DIR}/azule/entity/Component.h
	${PROJECT_INCLUDE_DIR}/azule/entity/Entity.h
	${PROJECT_INCLUDE_DIR}/azule/entity/EntityDatabase.h
	${PROJECT_INCLUDE_DIR}/azule/entity/EntityEvent.h
	${PROJECT_INCLUDE_DIR}/azule/entity/SelectionComponent.h
	${PROJECT_INCLUDE_DIR}/azule/entity/System.h
	${PROJECT_INCLUDE_DIR}/azule/entity/TransformComponent.h
)

set(ENTITY_SRC_LIST
	entity/Animation.cpp
	entity/AnimationChannel.cpp
	entity/AnimationComponent.cpp
	entity/AnimationSystem.cpp
	entity/CloneSystem.cpp
	entity/Component.cpp
	entity/Entity.cpp
	entity/EntityDatabase.cpp
	entity/EntityEvent.cpp
	entity/SelectionComponent.cpp
	entity/System.cpp
	entity/TransformComponent.cpp
)

if(MSVC)
	source_group("Header Files\\entity" FILES ${ENTITY_H_LIST})
	source_group("Source Files\\entity" FILES ${ENTITY_SRC_LIST})
endif()

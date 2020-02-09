project(age-entity)

AGE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/entity/Entity.h
	${AGE_INCLUDE_DIR}/age/entity/EntityDatabase.h
	${AGE_INCLUDE_DIR}/age/entity/EntityEvent.h
	${AGE_INCLUDE_DIR}/age/entity/HealthComponent.h
	${AGE_INCLUDE_DIR}/age/entity/SelectionComponent.h
	${AGE_INCLUDE_DIR}/age/entity/System.h
	${AGE_INCLUDE_DIR}/age/entity/TransformComponent.h
	${AGE_INCLUDE_DIR}/age/entity/Animation.h
	${AGE_INCLUDE_DIR}/age/entity/AnimationChannel.h
	${AGE_INCLUDE_DIR}/age/entity/AnimationComponent.h
	${AGE_INCLUDE_DIR}/age/entity/AnimationSystem.h
	${AGE_INCLUDE_DIR}/age/entity/CloneSystem.h
	${AGE_INCLUDE_DIR}/age/entity/Component.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Entity.cpp
	EntityDatabase.cpp
	EntityEvent.cpp
	HealthComponent.cpp
	Plugin.cpp
	SelectionComponent.cpp
	System.cpp
	TransformComponent.cpp
	Animation.cpp
	AnimationChannel.cpp
	AnimationComponent.cpp
	AnimationSystem.cpp
	CloneSystem.cpp
	Component.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-math
)

AGE_INCLUDE_BOOST()

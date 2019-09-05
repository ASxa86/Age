project(AgeEntity)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER age
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	Animation.h
	AnimationChannel.h
	AnimationComponent.h
	AnimationSystem.h
	CloneSystem.h
	Component.h
	Entity.h
	EntityDatabase.h
	EntityEvent.h
	Export.h
	HealthComponent.h
	SelectionComponent.h
	System.h
	TransformComponent.h
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
	HealthComponent.cpp
	Plugin.cpp
	SelectionComponent.cpp
	System.cpp
	TransformComponent.cpp
)

target_link_libraries(${PROJECT_NAME} AgeCore AgeMath)

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
	Component.h
	ComponentFactory.h
	ComponentPool.h
	Entity.h
	EntityEvent.h
	EntityManager.h
	Export.h
	System.h
	TransformComponent.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Animation.cpp
	AnimationChannel.cpp
	AnimationComponent.cpp
	AnimationSystem.cpp
	Component.cpp
	ComponentFactory.cpp
	ComponentFactoryRegister.cpp
	ComponentPool.cpp
	Entity.cpp
	EntityEvent.cpp
	EntityManager.cpp
	System.cpp
	TransformComponent.cpp
)

target_link_libraries(${PROJECT_NAME} AgeCore AgeMath)

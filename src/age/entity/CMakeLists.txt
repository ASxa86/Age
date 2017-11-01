project(AgeEntity)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	Component.h
	ComponentPool.h
	EntityManager.h
	Export.h
	FixedSystem.h
	System.h
	SystemManager.h
	VariableSystem.h
)

set(TARGET_SRC
	Component.cpp
	EntityManager.cpp
	FixedSystem.cpp
	System.cpp
	SystemManager.cpp
	VariableSystem.cpp	
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})
target_link_libraries(${PROJECT_NAME} AgeCore)

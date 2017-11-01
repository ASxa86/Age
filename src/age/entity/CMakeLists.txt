project(AgeEntity)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	Component.h
	ComponentPool.h
	Export.h
	EntityManager.h
	EntityProcessor.h
	FixedSystem.h
	System.h
	VariableSystem.h
)

set(TARGET_SRC
	Component.cpp
	EntityManager.cpp
	EntityProcessor.cpp
	FixedSystem.cpp
	System.cpp
	VariableSystem.cpp	
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})
target_link_libraries(${PROJECT_NAME} AgeCore ${ENTITYX_LIBRARY})

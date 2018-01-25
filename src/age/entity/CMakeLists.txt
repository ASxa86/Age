project(AgeEntity)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	Component.h
	ComponentPool.h
	Entity.h
	EntityEvent.h
	EntityManager.h
	Export.h
	System.h
)

set(TARGET_SRC
	Component.cpp
	ComponentPool.cpp
	Entity.cpp
	EntityEvent.cpp
	EntityManager.cpp
	System.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})
target_link_libraries(${PROJECT_NAME} AgeCore)

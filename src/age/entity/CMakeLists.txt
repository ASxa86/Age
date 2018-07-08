project(AgeEntity)

add_library(${PROJECT_NAME} SHARED "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	ComponentPool.h
	Entity.h
	EntityEvent.h
	EntityManager.h
	Export.h
	System.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ComponentPool.cpp
	Entity.cpp
	EntityEvent.cpp
	EntityManager.cpp
	System.cpp
)

target_link_libraries(${PROJECT_NAME} AgeCore)

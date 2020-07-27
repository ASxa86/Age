project(azule-entity-test)

find_package(EnTT)

AZULE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	ComponentPool.test.cpp
	EntityEvent.test.cpp
	EntityManager.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core
	azule-entity
	EnTT::EnTT
)

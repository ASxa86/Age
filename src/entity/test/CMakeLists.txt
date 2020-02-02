project(age-entity-test)

find_package(EnTT)

AGE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	ComponentPool.test.cpp
	EntityEvent.test.cpp
	EntityManager.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-entity
	EnTT
	# EnTT::EnTT
)

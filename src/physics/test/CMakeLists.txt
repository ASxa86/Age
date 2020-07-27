project(age-physics-test)

AGE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	PhysicsSystem.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-physics
)

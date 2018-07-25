project(TestAgePhysics)

set(TARGET_SRC
	PhysicsSystem.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_link_libraries(${PROJECT_NAME}
	AgePhysics
	GTest::GTest
	GTest::Main
)

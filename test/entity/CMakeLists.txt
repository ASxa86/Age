project(TestAgeEntity)

set(TARGET_SRC
	ComponentPool.test.cpp
	EntityEvent.test.cpp
	EntityManager.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_link_libraries(${PROJECT_NAME}
	AgeEntity
	GTest::GTest
	GTest::Main
)

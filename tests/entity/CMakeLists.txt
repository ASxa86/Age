project(TestAgeEntity)

find_package(EnTT)

set(TARGET_SRC
	ComponentPool.test.cpp
	EntityEvent.test.cpp
	EntityManager.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tests
)

target_link_libraries(${PROJECT_NAME}
	AgeEntity
	GTest::GTest
	GTest::Main
	EnTT
)

project(TestAgeEntity)

set(TARGET_SRC
	EntityManager.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_link_libraries(${PROJECT_NAME}
	AgeEntity
	${GTEST_LIBRARY}
)

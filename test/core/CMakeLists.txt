project(TestAgeCore)

set(TARGET_SRC
	Object.test.cpp
	Observer.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_link_libraries(${PROJECT_NAME}
	AgeCore
	${GTEST_LIBRARY}
)

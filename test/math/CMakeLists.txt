project(TestAgeMath)

set(TARGET_SRC
	Vector.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_link_libraries(${PROJECT_NAME}
	AgeMath
	${GTEST_LIBRARY}
)

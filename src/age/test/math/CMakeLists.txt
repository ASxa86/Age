project(TestAgeMath)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	Functions.test.cpp
	Vector.test.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tests
)

target_link_libraries(${PROJECT_NAME}
	AgeMath
	GTest::GTest
	GTest::Main
)

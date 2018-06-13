project(TestAgeCore)

set(TARGET_SRC
	Engine.test.cpp
	Object.test.cpp
	Observer.test.cpp
	Timer.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_link_libraries(${PROJECT_NAME}
	AgeCore
	GTest::GTest
	GTest::Main
)

project(TestAgeCore)

set(TARGET_SRC
	Engine.test.cpp
	Object.test.cpp
	Observer.test.cpp
	Properties.test.cpp
	String.test.cpp
	Timer.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tests
)

target_link_libraries(${PROJECT_NAME}
	AgeCore
	GTest::GTest
	GTest::Main
)

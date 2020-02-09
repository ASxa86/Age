project(age-core-test)

AGE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	Engine.test.cpp
	Object.test.cpp
	Observer.test.cpp
	Properties.test.cpp
	Timer.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-utilities
)

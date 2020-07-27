project(azule-core-test)

AZULE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	Engine.test.cpp
	Object.test.cpp
	Observer.test.cpp
	Reflection.test.cpp
	Timer.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core
	azule-utilities
)

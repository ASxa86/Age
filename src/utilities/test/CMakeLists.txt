project(age-utilities-test)

AGE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	Reflection.test.cpp
	SharedLibrary.test.cpp
	String.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-utilities
)

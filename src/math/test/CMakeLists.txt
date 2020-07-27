project(azule-math-test)

AZULE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	Functions.test.cpp
	Vector.test.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tests
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-math
)

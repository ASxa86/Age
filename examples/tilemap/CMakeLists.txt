project(age-tilemap)

find_package(SFML 2 COMPONENTS system graphics window)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER examples
)

target_sources(${PROJECT_NAME} PRIVATE
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-graphics
	sfml-graphics
)

AGE_COMPILE_OPTIONS()
AGE_WARNINGS_AS_ERRORS()
AGE_INSTALL()

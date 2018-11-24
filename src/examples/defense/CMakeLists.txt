project(AgeDefense)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER examples
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AgeGraphics
)
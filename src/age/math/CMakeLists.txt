project(AgeMath)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER age
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	Constants.h
	Convert.h
	Export.h
	Functions.h
	Vector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Functions.cpp
	Vector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AgeCore
)

project(AgeMath)

add_library(${PROJECT_NAME} SHARED)
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

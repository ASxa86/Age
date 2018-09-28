project(AgeMath)

add_library(${PROJECT_NAME} SHARED "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	BoundingBox.h
	BoundingCircle.h
	Export.h
	Intersect.h
	Vector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	BoundingBox.cpp
	BoundingCircle.cpp
	Intersect.cpp
	Vector.cpp
)

project(AgeMath)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	BoundingBox.h
	BoundingCircle.h
	Export.h
	Intersect.h
	TransformComponent.h
	Vector.h
)

set(TARGET_SRC
	BoundingBox.cpp
	BoundingCircle.cpp
	Intersect.cpp
	TransformComponent.cpp
	Vector.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

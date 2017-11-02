project(AgeMath)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	Export.h
	TransformComponent.h
)

set(TARGET_SRC
	TransformComponent.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

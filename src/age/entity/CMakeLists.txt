project(AgeEntity)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	Export.h
	Entity.h
	System.h
)

set(TARGET_SRC
	Entity.cpp
	System.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

project(AgePhysics)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	Export.h
	KinematicComponent.h
	KinematicSystem.h
)

set(TARGET_SRC
	KinematicComponent.cpp
	KinematicSystem.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

target_link_libraries(${PROJECT_NAME}
	AgeCore
)

project(azule-defense)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER examples
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		${CMAKE_DL_LIBS}
		GL
	)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core
	azule-graphics
	azule-navigation
	azule-physics
)

AZULE_COMPILE_OPTIONS()
AZULE_WARNINGS_AS_ERRORS()
AZULE_INSTALL()

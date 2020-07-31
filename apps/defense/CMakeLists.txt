project(azule-defense)

add_executable(${PROJECT_NAME})

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
	azule
)

AZULE_COMPILE_OPTIONS()
AZULE_WARNINGS_AS_ERRORS()
AZULE_INSTALL()

project(azule-animation)

find_package(SFML 2 CONFIG REQUIRED COMPONENTS system graphics window)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER examples
)

target_sources(${PROJECT_NAME} PRIVATE
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE azule)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PRIVATE
		-lGL
	)
endif()

AZULE_COMPILE_OPTIONS()
AZULE_WARNINGS_AS_ERRORS()
AZULE_INSTALL()

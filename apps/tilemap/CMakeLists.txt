project(azule-tilemap)

find_package(SFML 2 COMPONENTS system graphics window)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	sfml-graphics
)

project_install_target()
project_compile_options()

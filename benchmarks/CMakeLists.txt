project(benchmark-azule)

add_executable(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE -DCELERO_STATIC)

target_sources(${PROJECT_NAME} PRIVATE
	Copy.benchmark.cpp
	Create.benchmark.cpp
	Destroy.benchmark.cpp
	Iteration.benchmark.cpp
	main.cpp
	Object.h
)

find_package(celero CONFIG REQUIRED)
find_package(EntityX)
find_package(EnTT)

set(ENTITYX_LIBRARIES debug ${ENTITYX_LIBRARY_DEBUG} optimized ${ENTITYX_LIBRARY})

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	celero
	${ENTITYX_LIBRARIES}
	EnTT::EnTT
)

project_install_target()
project_compile_options()


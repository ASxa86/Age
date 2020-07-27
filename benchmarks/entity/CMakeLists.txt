project(age-entity-benchmark)

add_executable(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DCELERO_STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER benchmarks
)

find_package(EntityX)
find_package(EnTT)

target_sources(${PROJECT_NAME} PRIVATE
	Copy.benchmark.cpp
	Create.benchmark.cpp
	Destroy.benchmark.cpp
	Iteration.benchmark.cpp
	main.cpp
	Object.h
)

set(ENTITYX_LIBRARIES debug ${ENTITYX_LIBRARY_DEBUG} optimized ${ENTITYX_LIBRARY})

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-entity
	celero
	${ENTITYX_LIBRARIES}
	EnTT::EnTT
)

AZULE_COMPILE_OPTIONS()
AZULE_WARNINGS_AS_ERRORS()

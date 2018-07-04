project(BenchmarkAgeEntity)

add_executable(${PROJECT_NAME} "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -DCELERO_STATIC)

find_package(EntityX)

target_sources(${PROJECT_NAME} PRIVATE
	Copy.benchmark.cpp
	Create.benchmark.cpp
	Destroy.benchmark.cpp
	Iteration.benchmark.cpp
	main.cpp
	Object.h
)

set(ENTITYX_LIBRARIES debug ${ENTITYX_LIBRARY_DEBUG} optimized ${ENTITYX_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE AgeEntity celero ${ENTITYX_LIBRARIES})
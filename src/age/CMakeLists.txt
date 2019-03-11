add_subdirectory(audio)
add_subdirectory(core)
add_subdirectory(entity)
add_subdirectory(examples)
add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(navigation)
add_subdirectory(physics)
add_subdirectory(plugins)
add_subdirectory(terrain)
add_subdirectory(test)

option(AGE_ENABLE_BENCHMARKS "Enable building the AGE benchmark suite." OFF)
option(AGE_ENABLE_QT "Enable building the AGE benchmark suite." ON)

if(${AGE_ENABLE_BENCHMARKS})
	add_subdirectory(benchmark)
endif()

if(${AGE_ENABLE_QT})
	###############################################
	#
	#	Find Qt
	#
	find_package(Qt5 COMPONENTS Core Gui Widgets)
	set(CMAKE_AUTOMOC ON)

	###############################################
	#
	#	Find RTTR
	#
	find_package(RTTR)

	add_subdirectory(qt)
	add_subdirectory(tools)
endif()

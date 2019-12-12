option(BUILD_SHARED_LIBS "Enable building as shared libraries." ON)
option(AGE_ENABLE_WARNINGS_AS_ERRORS "Treat all compile warnings as errors." ON)
option(AGE_ENABLE_QT "Enable building the AGE benchmark suite." ON)
option(AGE_ENABLE_TESTS "Enable building test applications." ON)

macro(AGE_COMPILE_OPTIONS)
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
		target_compile_options(${PROJECT_NAME} PRIVATE /wd4251) # w4251 - 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
		target_compile_options(${PROJECT_NAME} PRIVATE /wd4275) # w4275 - non dll-interface class 'std::runtime_error' used as base for dll-interface class
		target_compile_options(${PROJECT_NAME} PRIVATE /MP)
		target_compile_options(${PROJECT_NAME} PRIVATE /D_SCL_SECURE_NO_WARNINGS)
		target_compile_options(${PROJECT_NAME} PRIVATE /permissive-)
		target_compile_options(${PROJECT_NAME} PRIVATE /std:c++17)

	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
		target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17)

	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
		target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17)

	endif()
endmacro()

macro(AGE_WARNINGS_AS_ERRORS)
	if(AGE_ENABLE_WARNINGS_AS_ERRORS)
		if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
			target_compile_options(${PROJECT_NAME} PRIVATE "/WX")

		elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
			target_compile_options(${PROJECT_NAME} PRIVATE "-Werror")

		elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
			target_compile_options(${PROJECT_NAME} PRIVATE "-Werror")
			
		endif()
	endif()
endmacro()

macro(AGE_EXPORTS)
	string(SUBSTRING ${PROJECT_NAME} 4 -1 EXPORT_FOLDER_NAME)
	string(REPLACE "-" "/" EXPORT_FOLDER_NAME ${EXPORT_FOLDER_NAME})
	set(EXPORT_FOLDER_DIR ${CMAKE_BINARY_DIR}/age/${EXPORT_FOLDER_NAME})
	generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${EXPORT_FOLDER_DIR}/export.h BASE_NAME ${PROJECT_NAME})

	# https://stackoverflow.com/questions/25676277/cmake-target-include-directories-prints-an-error-when-i-try-to-add-the-source
	target_include_directories(${PROJECT_NAME} PUBLIC
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
		$<INSTALL_INTERFACE:include>
	)

	install(FILES ${EXPORT_FOLDER_DIR}/export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/age/${EXPORT_FOLDER_NAME})
endmacro()

macro(AGE_QT)
	if(AGE_ENABLE_QT)
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/qt)
			add_subdirectory(qt)
		endif()
	endif()
endmacro()

macro(AGE_INCLUDE_QT)
	find_package(Qt5 COMPONENTS Core Gui Widgets)

	target_link_libraries(${PROJECT_NAME} PRIVATE
		Qt5::Core
		Qt5::Gui
		Qt5::Widgets
	)	
endmacro()

macro(AGE_TEST)
	if(AGE_ENABLE_TESTS)
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test)
			add_subdirectory(test)
		endif()
	endif()
endmacro()

macro(AGE_INCLUDE_GTEST)
	find_package(GTest REQUIRED)

	target_link_libraries(${PROJECT_NAME} PRIVATE
		GTest::GTest
		GTest::Main
	)	
endmacro()

macro(AGE_INCLUDE_BOOST)
	find_package(Boost COMPONENTS system filesystem)

	target_link_libraries(${PROJECT_NAME} PRIVATE
		Boost::system
		Boost::filesystem
	)
endmacro()

macro(AGE_ADD_LIBRARY)
	add_library(${PROJECT_NAME})

	set_target_properties(${PROJECT_NAME} PROPERTIES
		FOLDER age
	)	

	AGE_COMPILE_OPTIONS()
	AGE_WARNINGS_AS_ERRORS()
	AGE_EXPORTS()
	AGE_TEST()
	AGE_QT()
endmacro()

macro(AGE_ADD_TEST)
	add_executable(${PROJECT_NAME})

	set_target_properties(${PROJECT_NAME} PROPERTIES
		FOLDER tests
	)	

	AGE_COMPILE_OPTIONS()
	AGE_WARNINGS_AS_ERRORS()
	AGE_INCLUDE_GTEST()
endmacro()

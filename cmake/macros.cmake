option(BUILD_SHARED_LIBS "Enable building as shared libraries." ON)
option(AZULE_ENABLE_WARNINGS_AS_ERRORS "Treat all compile warnings as errors." ON)
option(AZULE_ENABLE_QT "Enable building the AGE benchmark suite." ON)
option(AZULE_ENABLE_TESTS "Enable building test applications." ON)
option(AZULE_ENABLE_BENCHMARKS "Enable building benchmark applications." OFF)

macro(AZULE_COMPILE_OPTIONS)
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

macro(AZULE_WARNINGS_AS_ERRORS)
	if(AZULE_ENABLE_WARNINGS_AS_ERRORS)
		if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
			target_compile_options(${PROJECT_NAME} PRIVATE "/WX")

		elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
			target_compile_options(${PROJECT_NAME} PRIVATE "-Werror")

		elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
			target_compile_options(${PROJECT_NAME} PRIVATE "-Werror")

		endif()
	endif()
endmacro()

macro(AZULE_EXPORTS)
	string(REPLACE "-" "/" EXPORT_FOLDER_NAME ${PROJECT_NAME})
	set(EXPORT_FOLDER_DIR ${CMAKE_BINARY_DIR}/${EXPORT_FOLDER_NAME})
	generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${EXPORT_FOLDER_DIR}/export.h BASE_NAME ${PROJECT_NAME})

	# https://stackoverflow.com/questions/25676277/cmake-target-include-directories-prints-an-error-when-i-try-to-add-the-source
	target_include_directories(${PROJECT_NAME} PUBLIC
		$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
		$<INSTALL_INTERFACE:include>
	)

	install(FILES ${EXPORT_FOLDER_DIR}/export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${EXPORT_FOLDER_NAME})
endmacro()

macro(AZULE_INSTALL)
	install(TARGETS ${PROJECT_NAME}
		EXPORT azule-config
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
endmacro()

macro(AZULE_INCLUDE_GTEST)
	find_package(GTest CONFIG REQUIRED)

	target_link_libraries(${PROJECT_NAME} PRIVATE
		GTest::gtest
		GTest::gtest_main
	)
endmacro()

macro(AZULE_ADD_LIBRARY)
	add_library(${PROJECT_NAME})

	set_target_properties(${PROJECT_NAME} PROPERTIES
		FOLDER azule
	)

	AZULE_COMPILE_OPTIONS()
	AZULE_WARNINGS_AS_ERRORS()
	AZULE_EXPORTS()
	AZULE_INSTALL()
endmacro()

macro(AZULE_ADD_TEST)
	add_executable(${PROJECT_NAME})

	set_target_properties(${PROJECT_NAME} PROPERTIES
		FOLDER tests
	)

	AZULE_COMPILE_OPTIONS()
	AZULE_WARNINGS_AS_ERRORS()
	AZULE_INCLUDE_GTEST()
	AZULE_INSTALL()
endmacro()

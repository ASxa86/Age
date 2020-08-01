project(test-azule-qt)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxEnum.test.cpp
	main.cpp
	WidgetPropertyFactory.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	azule-qt
	GTest::gtest
	GTest::gtest_main
)

project_install_target()
project_compile_options()

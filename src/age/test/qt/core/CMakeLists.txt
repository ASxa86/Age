project(TestAgeCoreQt)

set(TARGET_SRC
	main.cpp
	WidgetPropertyFactory.test.cpp
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tests
)

target_link_libraries(${PROJECT_NAME}
	AgeCoreQt
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	GTest::GTest
)

project(age-editor)

set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME})

AGE_INCLUDE_QT()

qt5_add_resources(QT_RESOURCES ${CMAKE_SOURCE_DIR}/data/icons.qrc)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tools
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core
	age-core-qt
	age-entity
	age-graphics
	age-physics
	age-navigation
)

target_sources(${PROJECT_NAME} PRIVATE
	Application.h
	DialogComponents.h
	DockWidgetComponent.h
	DockWidgetEntity.h
	GUIComponent.h
	ListWidgetComponents.h
	MainWindow.h
	TreeWidgetEntity.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Application.cpp
	DialogComponents.cpp
	DockWidgetComponent.cpp
	DockWidgetEntity.cpp
	ListWidgetComponents.cpp
	MainWindow.cpp
	TreeWidgetEntity.cpp
	main.cpp
	${QT_RESOURCES}
)

AGE_COMPILE_OPTIONS()
AGE_WARNINGS_AS_ERRORS()

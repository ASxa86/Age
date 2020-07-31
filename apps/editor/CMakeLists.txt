project(azule-editor)

set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME})

find_package(Qt5 COMPONENTS Core Gui Widgets)

qt5_add_resources(QT_RESOURCES ${CMAKE_SOURCE_DIR}/data/icons.qrc)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

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

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	azule-qt
)

AZULE_COMPILE_OPTIONS()
AZULE_WARNINGS_AS_ERRORS()

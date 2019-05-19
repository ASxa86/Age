project(AgeEditor)

qt5_add_resources(QT_RESOURCES ${CMAKE_SOURCE_DIR}/data/icons.qrc)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tools
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AgeCore
	AgeCoreQt
	AgeEntity
	AgeGraphics
	AgePhysics
	AgeNavigation
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
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

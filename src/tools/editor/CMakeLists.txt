project(AgeEditor)

###############################################
#
#	Find RTTR
#
find_package(RTTR)

###############################################
#
#	Find Qt
#
find_package(Qt5 COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)

qt5_add_resources(QT_RESOURCES ${CMAKE_SOURCE_DIR}/data/icons.qrc)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER tools
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AgeCore
	AgeEntity
	AgeGraphics
	AgePhysics
	AgeNavigation
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	RTTR::Core
)

target_sources(${PROJECT_NAME} PRIVATE
	Application.h
	DialogComponents.h
	DockWidgetEntity.h
	ListWidgetComponents.h
	MainWindow.h
	Properties.h
	TreeWidgetEntity.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Application.cpp
	DialogComponents.cpp
	DockWidgetEntity.cpp
	ListWidgetComponents.cpp
	MainWindow.cpp
	Properties.cpp
	TreeWidgetEntity.cpp
	main.cpp
	${QT_RESOURCES}
)

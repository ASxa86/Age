project(AgeEditor)

find_package(Qt5 COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)

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
)

target_sources(${PROJECT_NAME} PRIVATE
	Application.h
	ComponentFactory.h
	MainWindow.h
	ListWidgetComponents.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Application.cpp
	ComponentFactory.cpp
	MainWindow.cpp
	ListWidgetComponents.cpp
	main.cpp
)

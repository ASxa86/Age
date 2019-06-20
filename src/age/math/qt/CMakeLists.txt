project(AgeMathQt)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER age/qt
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	-D${PROJECT_NAME}_Export
)

target_sources(${PROJECT_NAME} PRIVATE
	Export.h
	WidgetVector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	FactoryRegister.cpp
	WidgetVector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AgeCoreQt
	AgeMath
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)

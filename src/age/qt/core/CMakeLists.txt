project(AgeCoreQt)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER qt
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	-D${PROJECT_NAME}_Export
)

target_sources(${PROJECT_NAME} PRIVATE
	DelegateWidgetProperty.h
	Export.h
	TableModelProperties.h
	WidgetProperty.h
	WidgetPropertyBool.h
	WidgetPropertyFactory.h
)

target_sources(${PROJECT_NAME} PRIVATE
	DelegateWidgetProperty.cpp
	FactoryRegister.cpp
	TableModelProperties.cpp
	WidgetProperty.cpp
	WidgetPropertyBool.cpp
	WidgetPropertyFactory.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AgeCore
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)

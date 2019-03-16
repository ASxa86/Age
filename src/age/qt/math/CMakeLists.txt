project(AgeMathQt)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER qt
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	-D${PROJECT_NAME}_Export
)

target_sources(${PROJECT_NAME} PRIVATE
	Export.h
	WidgetVector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	WidgetVector.cpp
	Plugin.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	AgeCoreQt
	AgeMath
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	RTTR::Core
)

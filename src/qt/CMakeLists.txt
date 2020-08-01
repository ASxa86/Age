project(azule-qt)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/azule/qt/ComboBoxEnum.h
	${PROJECT_INCLUDE_DIR}/azule/qt/DelegateWidgetProperty.h
	${PROJECT_INCLUDE_DIR}/azule/qt/TableModelProperties.h
	${PROJECT_INCLUDE_DIR}/azule/qt/WidgetProperty.h
	${PROJECT_INCLUDE_DIR}/azule/qt/WidgetPropertyBool.h
	${PROJECT_INCLUDE_DIR}/azule/qt/WidgetPropertyFactory.h
	${PROJECT_INCLUDE_DIR}/azule/qt/WidgetVector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxEnum.cpp
	DelegateWidgetProperty.cpp
	FactoryRegister.cpp
	TableModelProperties.cpp
	WidgetProperty.cpp
	WidgetPropertyBool.cpp
	WidgetPropertyFactory.cpp
	WidgetVector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
)

find_package(Qt5 COMPONENTS Core Gui Widgets)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)

project_gen_export()
project_install_target()
project_compile_options()

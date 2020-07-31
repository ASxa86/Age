project(azule-qt)

set(CMAKE_AUTOMOC ON)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/qt/ComboBoxEnum.h
	${AZULE_INCLUDE_DIR}/azule/qt/DelegateWidgetProperty.h
	${AZULE_INCLUDE_DIR}/azule/qt/TableModelProperties.h
	${AZULE_INCLUDE_DIR}/azule/qt/WidgetProperty.h
	${AZULE_INCLUDE_DIR}/azule/qt/WidgetPropertyBool.h
	${AZULE_INCLUDE_DIR}/azule/qt/WidgetPropertyFactory.h
	${AZULE_INCLUDE_DIR}/azule/qt/WidgetVector.h
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

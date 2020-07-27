project(azule-core-qt)

set(CMAKE_AUTOMOC ON)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/core/qt/ComboBoxEnum.h
	${AZULE_INCLUDE_DIR}/azule/core/qt/DelegateWidgetProperty.h
	${AZULE_INCLUDE_DIR}/azule/core/qt/TableModelProperties.h
	${AZULE_INCLUDE_DIR}/azule/core/qt/WidgetProperty.h
	${AZULE_INCLUDE_DIR}/azule/core/qt/WidgetPropertyBool.h
	${AZULE_INCLUDE_DIR}/azule/core/qt/WidgetPropertyFactory.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxEnum.cpp
	DelegateWidgetProperty.cpp
	FactoryRegister.cpp
	TableModelProperties.cpp
	WidgetProperty.cpp
	WidgetPropertyBool.cpp
	WidgetPropertyFactory.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core
	azule-utilities
)

AZULE_INCLUDE_QT()
AZULE_INCLUDE_BOOST()

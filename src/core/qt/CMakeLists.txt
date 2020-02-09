project(age-core-qt)

set(CMAKE_AUTOMOC ON)

AGE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/core/qt/ComboBoxEnum.h
	${AGE_INCLUDE_DIR}/age/core/qt/DelegateWidgetProperty.h
	${AGE_INCLUDE_DIR}/age/core/qt/TableModelProperties.h
	${AGE_INCLUDE_DIR}/age/core/qt/WidgetProperty.h
	${AGE_INCLUDE_DIR}/age/core/qt/WidgetPropertyBool.h
	${AGE_INCLUDE_DIR}/age/core/qt/WidgetPropertyFactory.h
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
	age-core
	age-utilities
)

AGE_INCLUDE_QT()
AGE_INCLUDE_BOOST()

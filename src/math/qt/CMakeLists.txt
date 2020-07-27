project(azule-math-qt)

set(CMAKE_AUTOMOC ON)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/math/qt/WidgetVector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	FactoryRegister.cpp
	WidgetVector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core-qt
	azule-math
)

AZULE_INCLUDE_QT()

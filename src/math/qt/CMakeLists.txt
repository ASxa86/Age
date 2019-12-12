project(age-math-qt)

set(CMAKE_AUTOMOC ON)

AGE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/math/qt/WidgetVector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	FactoryRegister.cpp
	WidgetVector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-core-qt
	age-math
)

AGE_INCLUDE_QT()

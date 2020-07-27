project(azule-core-qt-test)

AZULE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxEnum.test.cpp
	main.cpp
	WidgetPropertyFactory.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-core-qt
)

AZULE_INCLUDE_QT()

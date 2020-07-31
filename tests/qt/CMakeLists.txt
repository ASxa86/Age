project(test-azule-qt)

AZULE_ADD_TEST()

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxEnum.test.cpp
	main.cpp
	WidgetPropertyFactory.test.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	azule-qt
)

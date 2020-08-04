project(azule-plugins-tmx)

############################################
#
#	FindPugi
#
find_package(PugiXML)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/azule/plugins/tmx/ParserTMX.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ParserTMX.cpp
	FactoryRegister.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	pugixml
	# pugixml::pugixml
)

project_install_target()
project_compile_options()

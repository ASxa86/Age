project(azule-plugins-tmx)

############################################
#
#	FindPugi
#
find_package(PugiXML)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/plugins/tmx/ParserTMX.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ParserTMX.cpp
	Reflection.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	pugixml
	# pugixml::pugixml
)

project(azule-plugins-xml)

############################################
#
#	FindPugi
#
find_package(PugiXML)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/plugins/xml/ParserXML.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ParserXML.cpp
	Reflection.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule
	pugixml
	# pugixml::pugixml
)

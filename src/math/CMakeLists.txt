project(azule-math)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/math/Constants.h
	${AZULE_INCLUDE_DIR}/azule/math/Convert.h
	${AZULE_INCLUDE_DIR}/azule/math/Functions.h
	${AZULE_INCLUDE_DIR}/azule/math/Vector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Functions.cpp
	Vector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-utilities
)

AZULE_INCLUDE_BOOST()

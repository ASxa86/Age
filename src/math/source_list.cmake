set(MATH_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/math/Constants.h
	${PROJECT_INCLUDE_DIR}/azule/math/Convert.h
	${PROJECT_INCLUDE_DIR}/azule/math/Functions.h
	${PROJECT_INCLUDE_DIR}/azule/math/Vector.h
)

set(MATH_SRC_LIST
	math/Functions.cpp
	math/Vector.cpp
)

if(MSVC)
	source_group("Header Files\\math" FILES ${MATH_H_LIST})
	source_group("Source Files\\math" FILES ${MATH_SRC_LIST})
endif()

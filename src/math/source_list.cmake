set(MATH_H_LIST
	${AZULE_INCLUDE_DIR}/azule/math/Constants.h
	${AZULE_INCLUDE_DIR}/azule/math/Convert.h
	${AZULE_INCLUDE_DIR}/azule/math/Functions.h
	${AZULE_INCLUDE_DIR}/azule/math/Vector.h
)

set(MATH_SRC_LIST
	math/Functions.cpp
	math/Vector.cpp
)

if(MSVC)
	source_group("Header Files\\math" FILES ${MATH_H_LIST})
	source_group("Source Files\\math" FILES ${MATH_SRC_LIST})
endif()

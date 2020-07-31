set(MATH_H_LIST
)

set(MATH_SRC_LIST
	math/Functions.test.cpp
	math/Vector.test.cpp
)

if(MSVC)
	source_group("Header Files\\math" FILES ${MATH_H_LIST})
	source_group("Source Files\\math" FILES ${MATH_SRC_LIST})
endif()

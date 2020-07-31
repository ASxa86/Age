set(UTILITIES_H_LIST
)

set(UTILITIES_SRC_LIST
	utilities/SharedLibrary.test.cpp
	utilities/String.test.cpp
)

if(MSVC)
	source_group("Header Files\\utilities" FILES ${UTILITIES_H_LIST})
	source_group("Source Files\\utilities" FILES ${UTILITIES_SRC_LIST})
endif()

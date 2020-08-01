set(UTILITIES_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/utilities/Pimpl.h
	${PROJECT_INCLUDE_DIR}/azule/utilities/PimplImpl.h
	${PROJECT_INCLUDE_DIR}/azule/utilities/TypeTraits.h
	${PROJECT_INCLUDE_DIR}/azule/utilities/SharedLibrary.h
	${PROJECT_INCLUDE_DIR}/azule/utilities/Signal.h
	${PROJECT_INCLUDE_DIR}/azule/utilities/StaticInvoke.h
	${PROJECT_INCLUDE_DIR}/azule/utilities/String.h
)

set(UTILITIES_SRC_LIST
	utilities/SharedLibrary.cpp
	utilities/String.cpp
)

if(MSVC)
	source_group("Header Files\\utilities" FILES ${UTILITIES_H_LIST})
	source_group("Source Files\\utilities" FILES ${UTILITIES_SRC_LIST})
endif()

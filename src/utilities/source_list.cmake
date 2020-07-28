set(UTILITIES_H_LIST
	${AZULE_INCLUDE_DIR}/azule/utilities/Pimpl.h
	${AZULE_INCLUDE_DIR}/azule/utilities/PimplImpl.h
	${AZULE_INCLUDE_DIR}/azule/utilities/SharedLibrary.h
	${AZULE_INCLUDE_DIR}/azule/utilities/Signal.h
	${AZULE_INCLUDE_DIR}/azule/utilities/StaticInvoke.h
	${AZULE_INCLUDE_DIR}/azule/utilities/String.h
)

set(UTILITIES_SRC_LIST
	utilities/SharedLibrary.cpp
	utilities/String.cpp
)

if(MSVC)
	source_group("Header Files\\utilities" FILES ${UTILITIES_H_LIST})
	source_group("Source Files\\utilities" FILES ${UTILITIES_SRC_LIST})
endif()

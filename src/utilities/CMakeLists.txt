project(azule-utilities)

AZULE_ADD_LIBRARY()

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC dl stdc++fs)
endif()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/utilities/Pimpl.h
	${AZULE_INCLUDE_DIR}/azule/utilities/PimplImpl.h
	${AZULE_INCLUDE_DIR}/azule/utilities/SharedLibrary.h
	${AZULE_INCLUDE_DIR}/azule/utilities/Signal.h
	${AZULE_INCLUDE_DIR}/azule/utilities/StaticInvoke.h
	${AZULE_INCLUDE_DIR}/azule/utilities/String.h
)

target_sources(${PROJECT_NAME} PRIVATE
	SharedLibrary.cpp
	String.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
)

AZULE_INCLUDE_BOOST()

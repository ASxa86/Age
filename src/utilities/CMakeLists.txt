project(age-utilities)

AGE_ADD_LIBRARY()

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC dl stdc++fs)
endif()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/utilities/Pimpl.h
	${AGE_INCLUDE_DIR}/age/utilities/PimplImpl.h
	${AGE_INCLUDE_DIR}/age/utilities/SharedLibrary.h
	${AGE_INCLUDE_DIR}/age/utilities/Signal.h
	${AGE_INCLUDE_DIR}/age/utilities/StaticInvoke.h
	${AGE_INCLUDE_DIR}/age/utilities/String.h
)

target_sources(${PROJECT_NAME} PRIVATE
	SharedLibrary.cpp
	String.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
)

AGE_INCLUDE_BOOST()

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
)

target_sources(${PROJECT_NAME} PRIVATE
	SharedLibrary.cpp
)

AGE_INCLUDE_BOOST()

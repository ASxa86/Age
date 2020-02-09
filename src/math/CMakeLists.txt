project(age-math)

AGE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/math/Constants.h
	${AGE_INCLUDE_DIR}/age/math/Convert.h
	${AGE_INCLUDE_DIR}/age/math/Functions.h
	${AGE_INCLUDE_DIR}/age/math/Vector.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Functions.cpp
	Vector.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	age-utilities
)

AGE_INCLUDE_BOOST()

set(CORE_H_LIST
)

set(CORE_SRC_LIST
	core/Engine.test.cpp
	core/Object.test.cpp
	core/Observer.test.cpp
	core/Timer.test.cpp
)

if(MSVC)
	source_group("Header Files\\core" FILES ${CORE_H_LIST})
	source_group("Source Files\\core" FILES ${CORE_SRC_LIST})
endif()

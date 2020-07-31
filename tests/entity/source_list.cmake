set(ENTITY_H_LIST
)

set(ENTITY_SRC_LIST
	entity/EntityEvent.test.cpp
	entity/EntityManager.test.cpp
)

if(MSVC)
	source_group("Header Files\\entity" FILES ${ENTITY_H_LIST})
	source_group("Source Files\\entity" FILES ${ENTITY_SRC_LIST})
endif()

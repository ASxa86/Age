set(REFLECTION_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/reflection/Property.h
	${PROJECT_INCLUDE_DIR}/azule/reflection/PropertyTemplateMethod.h
	${PROJECT_INCLUDE_DIR}/azule/reflection/PropertyTemplateMember.h
	${PROJECT_INCLUDE_DIR}/azule/reflection/Properties.h
)

set(REFLECTION_SRC_LIST
	reflection/Property.cpp
	reflection/Properties.cpp
)

if(MSVC)
	source_group("Header Files\\reflection" FILES ${REFLECTION_H_LIST})
	source_group("Source Files\\reflection" FILES ${REFLECTION_SRC_LIST})
endif()

project(AgeCore)

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES
	FOLDER age
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
	${Boost_LIBRARIES}
)

target_sources(${PROJECT_NAME} PRIVATE
	ChildEvent.h
	Configuration.h
	Engine.h
	EngineState.h
	EngineStateEvent.h
	Event.h
	EventQueue.h
	Export.h
	Factory.h
	MetaEnum.h
	Object.h
	Parser.h
	Pimpl.h
	PimplImpl.h
	Processor.h
	Properties.h
	String.h
	Timer.h
	Utilities.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ChildEvent.cpp
	Configuration.cpp
	Engine.cpp
	EngineState.cpp
	EngineStateEvent.cpp
	Event.cpp
	EventQueue.cpp
	Factory.cpp
	Object.cpp
	Parser.cpp
	Processor.cpp
	Properties.cpp
	String.cpp
	Timer.cpp
	Utilities.cpp
)

project(AgeCore)

add_library(${PROJECT_NAME} SHARED "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs)
endif()

target_sources(${PROJECT_NAME} PRIVATE
	ChildEvent.h
	Configuration.h
	Engine.h
	EngineState.h
	EngineStateEvent.h
	Event.h
	EventQueue.h
	Export.h
	Object.h
	Pimpl.h
	PimplImpl.h
	Processor.h
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
	Object.cpp
	Processor.cpp
	Timer.cpp
	Utilities.cpp
)

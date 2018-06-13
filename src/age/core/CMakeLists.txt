project(AgeCore)

add_library(${PROJECT_NAME} SHARED "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	ChildEvent.h
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
)

target_sources(${PROJECT_NAME} PRIVATE
	ChildEvent.cpp
	Engine.cpp
	EngineState.cpp
	EngineStateEvent.cpp
	Event.cpp
	EventQueue.cpp
	Object.cpp
	Processor.cpp
	Timer.cpp
)

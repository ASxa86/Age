project(AgeCore)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	ChildEvent.h
	Engine.h
	EngineState.h
	EngineStateEvent.h
	Event.h
	EventQueue.h
	Export.h
	FixedProcessor.h
	Object.h
	Pimpl.h
	PimplImpl.h
	Processor.h
	VariableProcessor.h
)

set(TARGET_SRC
	ChildEvent.cpp
	Engine.cpp
	EngineState.cpp
	EngineStateEvent.cpp
	Event.cpp
	EventQueue.cpp
	FixedProcessor.cpp
	Object.cpp
	Processor.cpp
	VariableProcessor.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

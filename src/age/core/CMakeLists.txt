project(AgeCore)

add_definitions(-D${PROJECT_NAME}_Export)

set(TARGET_H
	ChildEvent.h
	Engine.h
	EngineState.h
	EngineStateEvent.h
	Entity.h
	Event.h
	EventQueue.h
	Export.h
	FixedSystem.h
	Object.h
	Pimpl.h
	PimplImpl.h
	RenderSystem.h
	System.h
	Timer.h
)

set(TARGET_SRC
	ChildEvent.cpp
	Engine.cpp
	EngineState.cpp
	EngineStateEvent.cpp
	Entity.cpp
	Event.cpp
	EventQueue.cpp
	FixedSystem.cpp
	Object.cpp
	RenderSystem.cpp
	System.cpp
	Timer.cpp
)

add_library(${PROJECT_NAME} SHARED ${TARGET_SRC} ${TARGET_H})

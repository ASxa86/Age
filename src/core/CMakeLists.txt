project(age-core)

AGE_ADD_LIBRARY()

if(UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC dl stdc++fs)
endif()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/core/ChildEvent.h
	${AGE_INCLUDE_DIR}/age/core/Configuration.h
	${AGE_INCLUDE_DIR}/age/core/Engine.h
	${AGE_INCLUDE_DIR}/age/core/EngineState.h
	${AGE_INCLUDE_DIR}/age/core/EngineStateEvent.h
	${AGE_INCLUDE_DIR}/age/core/Event.h
	${AGE_INCLUDE_DIR}/age/core/EventQueue.h
	${AGE_INCLUDE_DIR}/age/core/Factory.h
	${AGE_INCLUDE_DIR}/age/core/MagicEnum.h
	${AGE_INCLUDE_DIR}/age/core/Object.h
	${AGE_INCLUDE_DIR}/age/core/Parser.h
	${AGE_INCLUDE_DIR}/age/core/Pimpl.h
	${AGE_INCLUDE_DIR}/age/core/PimplImpl.h
	${AGE_INCLUDE_DIR}/age/core/Processor.h
	${AGE_INCLUDE_DIR}/age/core/Properties.h
	${AGE_INCLUDE_DIR}/age/core/String.h
	${AGE_INCLUDE_DIR}/age/core/Timer.h
	${AGE_INCLUDE_DIR}/age/core/Utilities.h
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

AGE_INCLUDE_BOOST()

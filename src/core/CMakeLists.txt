project(azule-core)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/core/ChildEvent.h
	${AZULE_INCLUDE_DIR}/azule/core/Configuration.h
	${AZULE_INCLUDE_DIR}/azule/core/Engine.h
	${AZULE_INCLUDE_DIR}/azule/core/EngineState.h
	${AZULE_INCLUDE_DIR}/azule/core/EngineStateEvent.h
	${AZULE_INCLUDE_DIR}/azule/core/Event.h
	${AZULE_INCLUDE_DIR}/azule/core/EventQueue.h
	${AZULE_INCLUDE_DIR}/azule/core/Object.h
	${AZULE_INCLUDE_DIR}/azule/core/Parser.h
	${AZULE_INCLUDE_DIR}/azule/core/Processor.h
	${AZULE_INCLUDE_DIR}/azule/core/Reflection.h
	${AZULE_INCLUDE_DIR}/azule/core/Timer.h
	${AZULE_INCLUDE_DIR}/azule/core/TypeTraits.h
	${AZULE_INCLUDE_DIR}/azule/core/Utilities.h
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
	Parser.cpp
	Processor.cpp
	Reflection.cpp
	Timer.cpp
	Utilities.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	azule-utilities
)

AZULE_INCLUDE_BOOST()

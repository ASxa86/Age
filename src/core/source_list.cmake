set(CORE_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/core/ChildEvent.h
	${PROJECT_INCLUDE_DIR}/azule/core/Configuration.h
	${PROJECT_INCLUDE_DIR}/azule/core/Engine.h
	${PROJECT_INCLUDE_DIR}/azule/core/EngineState.h
	${PROJECT_INCLUDE_DIR}/azule/core/EngineStateEvent.h
	${PROJECT_INCLUDE_DIR}/azule/core/Event.h
	${PROJECT_INCLUDE_DIR}/azule/core/EventQueue.h
	${PROJECT_INCLUDE_DIR}/azule/core/Object.h
	${PROJECT_INCLUDE_DIR}/azule/core/Parser.h
	${PROJECT_INCLUDE_DIR}/azule/core/Processor.h
	${PROJECT_INCLUDE_DIR}/azule/core/Reflection.h
	${PROJECT_INCLUDE_DIR}/azule/core/Timer.h
	${PROJECT_INCLUDE_DIR}/azule/core/Utilities.h
)

set(CORE_SRC_LIST
	core/ChildEvent.cpp
	core/Configuration.cpp
	core/Engine.cpp
	core/EngineState.cpp
	core/EngineStateEvent.cpp
	core/Event.cpp
	core/EventQueue.cpp
	core/Object.cpp
	core/Parser.cpp
	core/Processor.cpp
	core/Reflection.cpp
	core/Timer.cpp
	core/Utilities.cpp
)

if(MSVC)
	source_group("Header Files\\core" FILES ${CORE_H_LIST})
	source_group("Source Files\\core" FILES ${CORE_SRC_LIST})
endif()

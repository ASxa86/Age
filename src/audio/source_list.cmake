set(AUDIO_H_LIST
	${PROJECT_INCLUDE_DIR}/azule/audio/AudioEvent.h
	${PROJECT_INCLUDE_DIR}/azule/audio/AudioSystem.h
)

set(AUDIO_SRC_LIST
	audio/AudioEvent.cpp
	audio/AudioSystem.cpp
)

if(MSVC)
	source_group("Header Files\\audio" FILES ${AUDIO_H_LIST})
	source_group("Source Files\\audio" FILES ${AUDIO_SRC_LIST})
endif()

project(azule-audio)

############################################
#
#	Find SFML
#
find_package(SFML 2 CONFIG COMPONENTS audio)

AZULE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AZULE_INCLUDE_DIR}/azule/audio/AudioEvent.h
	${AZULE_INCLUDE_DIR}/azule/audio/AudioSystem.h
)

target_sources(${PROJECT_NAME} PRIVATE
	AudioEvent.cpp
	AudioSystem.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	azule-core
	azule-entity
	sfml-audio
)

project(age-audio)

############################################
#
#	Find SFML
#
find_package(SFML 2 CONFIG COMPONENTS audio)

AGE_ADD_LIBRARY()

target_sources(${PROJECT_NAME} PRIVATE
	${AGE_INCLUDE_DIR}/age/audio/AudioEvent.h
	${AGE_INCLUDE_DIR}/age/audio/AudioSystem.h
)

target_sources(${PROJECT_NAME} PRIVATE
	AudioEvent.cpp
	AudioSystem.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	age-core
	age-entity
	sfml-audio
)

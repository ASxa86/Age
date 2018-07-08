project(AgeAudio)

############################################
#
#	Find SFML
#
find_package(SFML 2 COMPONENTS audio)

add_library(${PROJECT_NAME} SHARED "")
target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	AudioEvent.h
	AudioSystem.h
	Export.h
)

target_sources(${PROJECT_NAME} PRIVATE
	AudioEvent.cpp
	AudioSystem.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	AgeCore
	AgeEntity
	sfml-audio
)

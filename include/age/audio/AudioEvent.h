#pragma once

#include <age/audio/export.h>
#include <age/core/Event.h>
#include <age/core/Pimpl.h>

namespace sf
{
	class SoundBuffer;
}

namespace age
{
	namespace audio
	{
		///
		///	\class AudioEvent
		///
		///	\brief An event to notify handlers to play a given sound buffer.
		///
		///	If an AudioSystem exists as a child of the engine, the provided sound buffer will
		///	be automatically played.
		///
		///	\date July 8, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_AUDIO_EXPORT AudioEvent : public age::core::Event
		{
		public:
			///
			///	\param x The sound buffer to be played.
			///
			AudioEvent(sf::SoundBuffer& x);
			~AudioEvent();

			///
			///	\return Get the sound buffer from this event.
			///
			sf::SoundBuffer& getSoundBuffer() const;

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

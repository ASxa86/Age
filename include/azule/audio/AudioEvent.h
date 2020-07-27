#pragma once

#include <azule/audio/export.h>
#include <azule/core/Event.h>
#include <azule/utilities/Pimpl.h>

namespace sf
{
	class SoundBuffer;
}

namespace azule
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
		class AZULE_AUDIO_EXPORT AudioEvent : public azule::core::Event
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

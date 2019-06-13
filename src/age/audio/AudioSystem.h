#pragma once

#include <age/audio/Export.h>
#include <age/entity/System.h>

namespace age
{
	namespace core
	{
		class Event;
	}

	namespace audio
	{
		///
		///	\class AudioSystem
		///
		///	\brief Handles playing event driven audio.
		///
		///	\date July 8, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_AUDIO_EXPORT AudioSystem : public age::entity::System
		{
		public:
			AudioSystem();
			~AudioSystem();

		protected:
			virtual void startup() override;
			virtual void onEvent(age::core::Event* x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

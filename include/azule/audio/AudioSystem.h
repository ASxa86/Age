#pragma once

#include <azule/audio/export.h>
#include <azule/entity/System.h>

namespace azule
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
		class AZULE_AUDIO_EXPORT AudioSystem : public azule::entity::System
		{
		public:
			AudioSystem();
			~AudioSystem();

		protected:
			virtual void onStartup() override;
			virtual void onEvent(azule::core::Event* x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

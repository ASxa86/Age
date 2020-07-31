#pragma once

#include <azule/entity/System.h>
#include <azule/export.h>

namespace azule
{
	class Event;

	///
	///	\class AudioSystem
	///
	///	\brief Handles playing event driven audio.
	///
	///	\date July 8, 2018
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT AudioSystem : public azule::System
	{
	public:
		AudioSystem();
		~AudioSystem();

	protected:
		virtual void onStartup() override;
		virtual void onEvent(azule::Event* x);

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

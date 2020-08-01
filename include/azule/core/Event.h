#pragma once

#include <azule/export.hxx>

namespace azule
{
	///
	///	\class Event
	///
	///	\brief This class manages the different event types that are available.
	///
	///	\date April 28, 2017
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT Event
	{
	public:
		Event();
		virtual ~Event();

		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;
	};
}

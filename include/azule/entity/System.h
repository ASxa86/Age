#pragma once

#include <azule/core/Processor.h>
#include <azule/export.hxx>
#include <chrono>

namespace azule
{
	class EntityDatabase;

	///
	///	\class Processor
	///
	///	\brief The System in Entity Component System. Override to process game logic for specific components on entities.
	///
	///	\date May 6, 2017
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT System : public azule::Processor
	{
	public:
		System();
		virtual ~System() override;

	protected:
		///
		///	Systems perform work on entities. This provides a convenient way to collect them.
		///
		EntityDatabase* getEntityDatabase() const;
	};
}

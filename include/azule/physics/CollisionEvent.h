#pragma once

#include <azule/core/Event.h>
#include <azule/export.h>
#include <azule/utilities/Pimpl.h>
#include <vector>

namespace azule
{
	class Entity;

	///
	///	\class Collision Event
	///
	///	\brief This event contains relevant information pertaining to a single collision between entities.
	///
	///	\date February 3, 2018
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT CollisionEvent : public azule::Event
	{
	public:
		///
		///	\param x The entity that collided.
		///
		CollisionEvent(const azule::Entity& a, const azule::Entity& b);
		~CollisionEvent() override;

		const azule::Entity& getEntityA();
		const azule::Entity& getEntityB();

	private:
		class Impl;
		Pimpl<Impl> pimpl;
	};
}

#pragma once

#include <azule/entity/Component.h>
#include <azule/export.hxx>

namespace azule
{
	///
	///	\struct CollisionComponent
	///
	///	\brief Base class of common data shared between all collision components.
	///
	///	\author Aaron Shelley
	///
	///	\date February 26, 2019
	///
	struct AZULE_EXPORT CollisionComponent : public azule::Component
	{
		CollisionComponent();

		///
		///	Restitution is used to make objects bounce.The restitution value is usually set to be between 0 and 1.
		///	Consider dropping a ball on a table.A value of zero means the ball won't bounce. This is called an
		///	inelastic collision. A value of one means the ball's velocity will be exactly reflected.
		///
		double Restitution{};

		///
		///	Friction is used to make objects slide along each other realistically.Box2D supports static and dynamic
		///	friction, but uses the same parameter for both.Friction is simulated accurately in Box2D and the friction
		///	strength is proportional to the normal force(this is called Coulomb friction).The friction parameter is
		///	usually set between 0 and 1, but can be any non - negative value.A friction value of 0 turns off friction
		///	and a value of 1 makes the friction strong.
		///
		double Friction{};

		///
		///	The fixture density is used to compute the mass properties of the parent body. The density can be zero
		///	or positive. You should generally use similar densities for all your fixtures.This will improve stacking
		///	stability.
		///
		double Density{};

		///
		///	Sometimes game logic needs to know when two fixtures overlap yet there should be no collision
		///	response. This is done by using sensors. A sensor is a fixture that detects collision but does not produce
		///	a response.
		///
		bool IsSensor{false};
	};
}

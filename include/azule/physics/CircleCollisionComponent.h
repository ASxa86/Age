#pragma once

#include <azule/physics/CollisionComponent.h>

namespace azule
{
	///
	///	\struct CircleCollisionComponent
	///
	///	\brief Define the size of a circle used to determine collision with other collision components.
	///
	///	\author Aaron Shelley
	///
	///	\date February 26, 2019
	///
	struct AZULE_EXPORT CircleCollisionComponent final : public CollisionComponent
	{
		CircleCollisionComponent();

		double Radius;
	};
}

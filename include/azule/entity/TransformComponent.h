#pragma once

#include <azule/entity/Component.h>
#include <azule/entity/export.h>
#include <azule/math/Vector.h>

namespace azule
{
	namespace entity
	{
		///
		///	\struct TransformComponent
		///
		///	\brief This component is given to entities that hold a position within the scene.
		///
		///	\date June 11, 2017
		///
		///	\author Aaron Shelley
		///
		struct AZULE_ENTITY_EXPORT TransformComponent : public Component
		{
			TransformComponent();

			azule::math::Vector Position{};
			double Rotation{};
		};
	}
}

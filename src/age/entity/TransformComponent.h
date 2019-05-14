#pragma once

#include <age/core/MetaEnum.h>
#include <age/entity/Component.h>
#include <age/entity/Export.h>
#include <age/math/Vector.h>

namespace age
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
		struct AGE_ENTITY_EXPORT TransformComponent : public Component
		{
			TransformComponent();

			age::math::Vector Position{};
			double Rotation{};
		};
	}
}

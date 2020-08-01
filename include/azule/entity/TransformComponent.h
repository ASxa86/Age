#pragma once

#include <azule/entity/Component.h>
#include <azule/export.hxx>
#include <azule/math/Vector.h>

namespace azule
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
	struct AZULE_EXPORT TransformComponent : public Component
	{
		TransformComponent();

		azule::Vector Position{};
		double Rotation{};
	};
}

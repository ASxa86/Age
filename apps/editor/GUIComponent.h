#pragma once

#include <azule/entity/Component.h>
#include <string>

namespace azule
{
	///
	///	\class GUIComponent
	///
	///	\brief A collection of data useful for GUI configuration such as ID labels.
	///
	///	\author Aaron Shelley
	///
	///	\date March 9, 2019
	///
	struct GUIComponent : public azule::Component
	{
		std::string ID;
	};
}

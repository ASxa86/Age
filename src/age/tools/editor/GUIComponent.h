#pragma once

#include <age/entity/Component.h>
#include <string>

namespace age
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
	struct GUIComponent : public age::entity::Component
	{
		std::string ID;
	};
}

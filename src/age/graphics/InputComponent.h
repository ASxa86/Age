#pragma once

#include <age/core/Object.h>
#include <age/graphics/Export.h>

namespace age
{
	namespace graphics
	{
		///
		///	\class InputComponent
		///
		///	\brief This is an input component that manages mapped keys for a given command.
		///
		///	This class is the container for the "Command Pattern" where mapped keys are used by the
		///	PlayerInputSystem to determine which command should be ran.
		///
		///	\date June 9, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT InputComponent : public age::core::Object
		{
		public:
			InputComponent();
			~InputComponent() override;
		};
	}
}

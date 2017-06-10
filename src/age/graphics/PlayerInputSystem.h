#pragma once

#include <age/graphics/Export.h>
#include <age/core/VariableSystem.h>

namespace age
{
	namespace core
	{
		class Event;
	}

	namespace graphics
	{
		///
		///	\class PlayerInputSystem
		///
		///	\brief This system manages controller/keyboard input for a player.
		///
		///	This class is built around the command pattern. Commands can be defined to handle different actions which 
		/// are defined to modify components of an entity with a PlayerInputComponent.
		///
		class AGE_GRAPHICS_EXPORT PlayerInputSystem : public age::core::VariableSystem
		{
		public:
			PlayerInputSystem();
			~PlayerInputSystem() override;

			///
			///	\brief Handles input events and forwards them on to InputComponents.
			///
			void event(age::core::Event* x);

			void frame(std::chrono::microseconds x) override;
		};
	}
}

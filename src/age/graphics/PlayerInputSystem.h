#pragma once

#include <age/graphics/Export.h>
#include <age/entity/System.h>

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
		///	are defined to modify components of an entity with a PlayerInputComponent.
		///
		///	\date June 9, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT PlayerInputSystem : public age::entity::System
		{
		public:
			PlayerInputSystem();
			~PlayerInputSystem() override;

			///
			///	Initialize input system to pick up keyboard events.
			///
			void initialize() override;

			///
			///	\brief Handles input events and forwards them on to InputComponents.
			///
			void event(age::core::Event* x);

			///
			///	Handle real time key down checking.
			///
			void frame(std::chrono::microseconds x);
		};
	}
}

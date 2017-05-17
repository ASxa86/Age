#pragma once

#include <age/core/RenderProcessor.h>
#include <age/entity/System.h>
#include <age/graphics/Export.h>

namespace age
{
	namespace graphics
	{
		///
		///	\class Window
		///
		///	\brief The graphics window for AGE. This handles rendering of objects within the engine.
		///
		///	This class acts as a RenderSystem for the Entity Component System.
		///
		///	\date May 6, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT Window : public age::core::RenderProcessor, public age::entity::System
		{
		public:
			Window(uint16_t width = 1280, uint16_t height = 720);
			~Window();

			virtual void pollEvents();

			virtual void frame(std::chrono::microseconds x);

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

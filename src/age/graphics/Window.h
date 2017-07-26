#pragma once

#include <age/core/RenderSystem.h>
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
		class AGE_GRAPHICS_EXPORT Window : public age::core::RenderSystem
		{
		public:
			Window(unsigned int width = 1280, unsigned int height = 720);
			~Window() override;

			///
			///	Get the current width of the window.
			///
			unsigned int getWidth() const;

			///
			///	Get the current height of the window.
			///
			unsigned int getHeight() const;

			void pollEvents() override;

			void frame(std::chrono::microseconds x) override;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

#pragma once

#include <azule/core/Processor.h>
#include <azule/export.h>

namespace azule
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
	class AZULE_EXPORT Window : public azule::Processor
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

		///
		///	Renders drawable components with the given pixel per meter ratio.
		///	(32pixels/m)
		///
		void setPixelsPerMeter(unsigned int x);

		///
		///	Get the number of pixels per meter use to render drawable components.
		///
		unsigned int getPixelsPerMeter() const;

	protected:
		void variable(std::chrono::microseconds x);
		void render(std::chrono::microseconds x);

	private:
		class Impl;
		Pimpl<Impl> pimpl;
	};
}

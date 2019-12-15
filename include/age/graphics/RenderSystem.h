#pragma once

#include <age/entity/System.h>
#include <age/graphics/export.h>

namespace sf
{
	class RenderTarget;
	class RenderStates;
}

namespace age
{
	namespace graphics
	{
		///
		///	\class RenderSystem
		///
		///	\brief An abstract class to override for specific rendering of renderable components.
		///
		///	\date February 19, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT RenderSystem : public age::entity::System
		{
		public:
			RenderSystem();
			virtual ~RenderSystem();

			///
			///	Override to render specific components for a derived render system.
			///
			///	\param target The target to render to.
			///	\param state The global render state. Generally contains scaling information from the Window parent.
			///	\param x The frame rate in microseconds.
			///
			virtual void render(sf::RenderTarget& target, std::chrono::microseconds x) = 0;
		};
	}
}

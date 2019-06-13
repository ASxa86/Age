#pragma once

#include <age/graphics/RenderSystem.h>
#include <age/physics/Export.h>

namespace age
{
	namespace physics
	{
		///
		///	\class PhysicsRenderSystem
		///
		///	\brief This draws bounding shapes around entities with physics components.
		///
		///	\author Aaron Shelley
		///
		///	\date July 26, 2018
		///
		class AGE_PHYSICS_EXPORT PhysicsRenderSystem : public age::graphics::RenderSystem
		{
		public:
			PhysicsRenderSystem();
			~PhysicsRenderSystem() override;

			void render(sf::RenderTarget& target, std::chrono::microseconds x) override;

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

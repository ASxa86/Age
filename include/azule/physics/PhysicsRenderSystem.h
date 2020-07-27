#pragma once

#include <azule/graphics/RenderSystem.h>
#include <azule/physics/export.h>

namespace azule
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
		class AZULE_PHYSICS_EXPORT PhysicsRenderSystem : public azule::graphics::RenderSystem
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

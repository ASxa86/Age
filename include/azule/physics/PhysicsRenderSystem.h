#pragma once

#include <azule/export.h>
#include <azule/graphics/RenderSystem.h>

namespace azule
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
	class AZULE_EXPORT PhysicsRenderSystem : public azule::RenderSystem
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

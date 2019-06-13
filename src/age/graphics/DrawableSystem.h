#include <age/graphics/RenderSystem.h>

namespace age
{
	namespace graphics
	{
		///
		///	\class DrawableSystem
		///
		///	\brief Render system for generic drawable.
		///
		///	Handles scaling pixels to a meter measurement.
		///
		///	\date February 19, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT DrawableSystem : public RenderSystem
		{
		public:
			DrawableSystem();
			~DrawableSystem() override;

			void render(sf::RenderTarget& target, std::chrono::microseconds x) override;

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

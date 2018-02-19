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
		///	\date February 19, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT DrawableSystem : public RenderSystem
		{
		public:
			DrawableSystem();
			~DrawableSystem() override;

			void render(sf::RenderTarget& target, sf::RenderStates& state, std::chrono::microseconds x) override;
		};
	}
}

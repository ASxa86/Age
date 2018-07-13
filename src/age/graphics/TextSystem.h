#include <age/graphics/RenderSystem.h>

namespace age
{
	namespace graphics
	{
		///
		///	\class TextSystem
		///
		///	\brief Render system for HUD text.
		///
		///	\date July 12, 2018
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT TextSystem : public RenderSystem
		{
		public:
			TextSystem();
			~TextSystem() override;

			void render(sf::RenderTarget& target, std::chrono::microseconds x) override;
		};
	}
}

#include <age/graphics/RenderSystem.h>
#include <age/math/Vector.h>

namespace age
{
	namespace graphics
	{
		///
		///	\class HealthBarSystem
		///
		///	\brief Render system for health components
		///
		///	\date September 4, 2019
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT HealthBarSystem : public RenderSystem
		{
		public:
			HealthBarSystem();
			~HealthBarSystem() override;

			void render(sf::RenderTarget& target, std::chrono::microseconds x) override;

			std::array<int, 4> Color{};
			age::math::Vector Offset{};
			age::math::Vector Size{};

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

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

			///
			///	Set the pixels per meter unit scaling for drawable objects.
			///	(32 pixels per meter)
			///
			void setPixelsPerMeter(unsigned int x);

			///
			///	Get the pixels per meter unit scaling.
			///
			unsigned int getPixelsPerMeter() const;

			void render(sf::RenderTarget& target, std::chrono::microseconds x) override;

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

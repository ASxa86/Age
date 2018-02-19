#pragma once

#include <age/graphics/SpriteAnimation.h>

namespace age
{
	namespace graphics
	{
		class AGE_GRAPHICS_EXPORT SpriteAnimationComponent
		{
		public:
			SpriteAnimationComponent();
			~SpriteAnimationComponent();

			SpriteAnimation& getCurrentAnimation();

		private:
			std::vector<SpriteAnimation> animations;
		};
	}
}

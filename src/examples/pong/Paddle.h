#pragma once

#include <age/core/Entity.h>
#include <age/math/Vector.h>

namespace age
{
	namespace pong
	{
		class Paddle : public age::core::Entity
		{
		public:
			Paddle();
			~Paddle() override;

			void setPosition(const age::math::Vector& x);
		};
	}
}

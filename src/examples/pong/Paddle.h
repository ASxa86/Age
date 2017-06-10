#pragma once

#include <age/core/Entity.h>

namespace age
{
	namespace pong
	{
		class Paddle : public age::core::Entity
		{
		public:
			Paddle();
			~Paddle() override;
		};
	}
}

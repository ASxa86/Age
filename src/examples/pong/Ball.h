#pragma once

#include <age/core/Entity.h>

namespace age
{
	namespace pong
	{
		class Ball : public age::core::Entity
		{
		public:
			Ball();
			~Ball() override;
		};
	}
}

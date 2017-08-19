#pragma once

#include <age/core/Engine.h>

namespace age
{
	namespace pong
	{
		class Pong
		{
		public:
			Pong();
			~Pong();

			int run();

		private:
			std::shared_ptr<age::core::Engine> engine;
		};
	}
}

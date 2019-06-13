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
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

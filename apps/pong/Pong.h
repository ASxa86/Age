#pragma once

#include <azule/core/Engine.h>

namespace azule
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

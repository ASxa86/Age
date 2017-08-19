#pragma once

#include <age/core/Entity.h>
#include <boost/qvm/vec.hpp>

namespace age
{
	namespace pong
	{
		class Paddle : public age::core::Entity
		{
		public:
			Paddle();
			~Paddle() override;

			void setPosition(const boost::qvm::vec<double, 2>& x);
		};
	}
}

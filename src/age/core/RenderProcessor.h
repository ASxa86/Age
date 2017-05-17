#pragma once

#include <age/core/Processor.h>

namespace age
{
	namespace core
	{
		class AGE_CORE_EXPORT RenderProcessor : public Processor
		{
		public:
			RenderProcessor();
			virtual ~RenderProcessor();

			virtual void pollEvents();
		};
	}
}

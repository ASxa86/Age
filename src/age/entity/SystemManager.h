#pragma once

#include <age/core/Processor.h>
#include <age/entity/Export.h>

namespace age
{
	namespace entity
	{
		class EntityManager;

		class AGE_ENTITY_EXPORT SystemManager : public age::core::Processor
		{
		public:
			SystemManager();
			~SystemManager() override;

		protected:
			void updateFixedSystems(std::chrono::microseconds x);
			void updateVariableSystems(std::chrono::microseconds x);
		};
	}
}

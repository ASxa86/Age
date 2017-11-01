#pragma once

#include <age/core/Processor.h>
#include <age/entity/Export.h>

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <entityx/entityx.h>

#ifdef WIN32
#pragma warning(pop)
#endif

namespace age
{
	namespace entity
	{
		class AGE_ENTITY_EXPORT EntityProcessor : public age::core::Processor
		{
		public:
			EntityProcessor();
			~EntityProcessor() override;

			entityx::EntityManager* getEntities();

		protected:
			void updateFixedSystems(std::chrono::microseconds x);
			void updateVariableSystems(std::chrono::microseconds x);

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

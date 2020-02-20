#pragma once

#include <age/core/Object.h>
#include <age/entity/export.h>

namespace age
{
	namespace entity


	{
		class Entity;

		class AGE_ENTITY_EXPORT EntityDatabase : public age::core::Object
		{
		public:
			bool addEntity(std::unique_ptr<age::entity::Entity> x);

			template <typename T = Entity>
			[[maybe_unused]] T* addEntity()
			{
				static_assert(std::is_base_of<age::entity::Entity, T>::value == true, "T must derive from age::entity::Entity.");

				auto child = std::make_unique<T>();
				const auto p = child.get();

				if(this->addEntity(std::move(child)) == true)
				{
					return p;
				}

				return nullptr;
			}

		private:
			using Object::addChild;
		};
	}
}

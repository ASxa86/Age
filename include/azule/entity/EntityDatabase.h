#pragma once

#include <azule/core/Object.h>
#include <azule/export.h>

namespace azule
{
	namespace entity


	{
		class Entity;

		class AZULE_EXPORT EntityDatabase : public azule::core::Object
		{
		public:
			bool addEntity(std::unique_ptr<azule::entity::Entity> x);

			template <typename T = Entity>
			[[maybe_unused]] T* addEntity()
			{
				static_assert(std::is_base_of<azule::entity::Entity, T>::value == true, "T must derive from azule::entity::Entity.");

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

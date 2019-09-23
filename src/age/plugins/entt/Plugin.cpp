#include <age/core/Factory.h>
#include <age/plugins/entt/EntityDatabase.h>

using namespace age::core;

namespace
{
	template <typename T>
	struct Creator : public age::core::CreatorBase
	{
		Object* create(Object* parent) const override
		{
			auto obj = std::make_unique<T>();
			auto p = obj.get();
			parent->addChild(std::move(obj));
			return p;
		}
	};
}

AGE_ENTT_EXPORT_C void FactoryRegister()
{
}

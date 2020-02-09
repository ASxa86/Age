#include <age/utilities/Reflection.h>
#include <age/entity/CloneSystem.h>
#include <age/entity/HealthComponent.h>
#include <age/entity/SelectionComponent.h>
#include <age/entity/TransformComponent.h>


#define ENTT_ID_TYPE std::size_t
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

using namespace age::entity;
using namespace age::utilities;

namespace
{
	class Entity;
	Register<Entity> reg([] {
		auto& type = Reflection::Add<CloneSystem>("CloneSystem");
		type.addProperty("Rate", &CloneSystem::Rate);
		type.addProperty("Limit", &CloneSystem::Limit);
		type.addProperty("Count", &CloneSystem::Count);

		type = Reflection::Add<Component>("Component");

		type = Reflection::Add<HealthComponent>("HealthComponent");
		type.addBase<Component>();
		type.addProperty("Health", &HealthComponent::Health);
		type.addProperty("HealthMax", &HealthComponent::HealthMax);

		type = Reflection::Add<SelectionComponent>("SelectionComponent");
		type.addBase<Component>();
		type.addProperty("Selected", &SelectionComponent::Selected);

		type = Reflection::Add<TransformComponent>("TransformComponent");
		type.addBase<Component>();
		type.addProperty("Position", &TransformComponent::Position);
		type.addProperty("Rotation", &TransformComponent::Rotation);
	});

	//class EnTT;
	//Register<EnTT> reg1([] {
	//	//std::hash<std::string_view> hash{};
	//	// auto factory = entt::reflect<Component>();

	//	//auto factory = entt::reflect<HealthComponent>(hash("HealthComponent"));
	//	//factory.base<Component>();
	//	//factory.data<&HealthComponent::Health>(hash("Health"));
	//	//factory.data<&HealthComponent::HealthMax>(hash("HealthMax"));

	//	//auto type = entt::resolve<HealthComponent>();
	//	//auto p = type.prop(hash("Health"));

	//	//HealthComponent c;
	//	//entt::meta_handle h{c};
	//	//h.type().prop(hash("Health")).value().cast<int>() = 3;
	//});
}
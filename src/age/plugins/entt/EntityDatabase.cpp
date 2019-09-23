#include <age/plugins/entt/Entity.h>
#include <age/plugins/entt/EntityDatabase.h>

#pragma warning(push, 0)
#include <entt/entt.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#pragma warning(pop)

using namespace age::entt;

EntityDatabase::EntityDatabase()
{
	//::entt::registry em;
	//auto e1 = em.create();
	//auto e = em.create(e1, em, ::entt::exclude_t<>());
	//(void)e;

	//this->addOnAddChild([&em](auto o) {
	//	auto entity = dynamic_cast<age::entt::Entity*>(o);
	//	if(entity != nullptr)
	//	{
	//		entity->entity_type = em.create();
	//		em.assign(entity->entity_type, char{});
	//	}
	//});
}
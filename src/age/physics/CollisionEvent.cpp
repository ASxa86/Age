#include <age/physics/CollisionEvent.h>

#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>

using namespace age::entity;
using namespace age::physics;

class CollisionEvent::Impl
{
public:
	Impl(Entity* a, Entity* b) : entityA{a}, entityB{b}
	{
	}

	Entity* entityA{};
	Entity* entityB{};
};

CollisionEvent::CollisionEvent(Entity* a, Entity* b) : age::core::Event(), pimpl{a, b}
{
}

CollisionEvent::~CollisionEvent()
{
}

age::entity::Entity* CollisionEvent::getEntityA()
{
	return this->pimpl->entityA;
}

age::entity::Entity* CollisionEvent::getEntityB()
{
	return this->pimpl->entityB;
}

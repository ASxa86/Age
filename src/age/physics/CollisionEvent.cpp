#include <age/physics/CollisionEvent.h>

#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>

using namespace age::entity;
using namespace age::physics;

class CollisionEvent::Impl
{
public:
	Impl(const Entity& a, const Entity& b) : entityA{a}, entityB{b}
	{
	}

	const Entity& entityA{};
	const Entity& entityB{};
};

CollisionEvent::CollisionEvent(const Entity& a, const Entity& b) : age::core::Event(), pimpl{a, b}
{
}

CollisionEvent::~CollisionEvent()
{
}

const age::entity::Entity& CollisionEvent::getEntityA()
{
	return this->pimpl->entityA;
}

const age::entity::Entity& CollisionEvent::getEntityB()
{
	return this->pimpl->entityB;
}

#include <azule/physics/CollisionEvent.h>

#include <azule/utilities/PimplImpl.h>
#include <azule/entity/Entity.h>

using namespace azule::entity;
using namespace azule::physics;

class CollisionEvent::Impl
{
public:
	Impl(const Entity& a, const Entity& b) : entityA{a}, entityB{b}
	{
	}

	const Entity& entityA{};
	const Entity& entityB{};
};

CollisionEvent::CollisionEvent(const Entity& a, const Entity& b) : azule::core::Event(), pimpl{a, b}
{
}

CollisionEvent::~CollisionEvent()
{
}

const azule::entity::Entity& CollisionEvent::getEntityA()
{
	return this->pimpl->entityA;
}

const azule::entity::Entity& CollisionEvent::getEntityB()
{
	return this->pimpl->entityB;
}

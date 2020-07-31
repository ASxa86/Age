#include <azule/physics/CollisionEvent.h>

#include <azule/utilities/PimplImpl.h>
#include <azule/entity/Entity.h>

using namespace azule;
using namespace azule;

class CollisionEvent::Impl
{
public:
	Impl(const Entity& a, const Entity& b) : entityA{a}, entityB{b}
	{
	}

	const Entity& entityA{};
	const Entity& entityB{};
};

CollisionEvent::CollisionEvent(const Entity& a, const Entity& b) : azule::Event(), pimpl{a, b}
{
}

CollisionEvent::~CollisionEvent()
{
}

const azule::Entity& CollisionEvent::getEntityA()
{
	return this->pimpl->entityA;
}

const azule::Entity& CollisionEvent::getEntityB()
{
	return this->pimpl->entityB;
}

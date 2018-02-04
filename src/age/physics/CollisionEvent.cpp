#include <age/physics/CollisionEvent.h>

#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>

using namespace age::entity;
using namespace age::physics;

class CollisionEvent::Impl
{
public:
	std::vector<Entity> entities;
};

CollisionEvent::CollisionEvent() : age::core::Event()
{
}

CollisionEvent::~CollisionEvent()
{
}

void CollisionEvent::addEntity(Entity x)
{
	this->pimpl->entities.push_back(x);
}

const std::vector<Entity>& CollisionEvent::getEntities() const
{
	return this->pimpl->entities;
}

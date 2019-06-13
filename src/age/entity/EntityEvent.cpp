#include <age/entity/Entity.h>
#include <age/entity/EntityEvent.h>

using namespace age::entity;

EntityEvent::EntityEvent(const Entity& e, Type t) : entity{e}, type{t}
{
}

EntityEvent::~EntityEvent()
{
}

const Entity& EntityEvent::getEntity() const
{
	return this->entity;
}

EntityEvent::Type EntityEvent::getType() const
{
	return this->type;
}

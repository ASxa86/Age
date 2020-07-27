#include <azule/entity/Entity.h>
#include <azule/entity/EntityEvent.h>

using namespace azule::entity;

EntityEvent::EntityEvent(Entity* e, Type t) : entity{e}, type{t}
{
}

EntityEvent::~EntityEvent()
{
}

Entity* EntityEvent::getEntity() const
{
	return this->entity;
}

EntityEvent::Type EntityEvent::getType() const
{
	return this->type;
}

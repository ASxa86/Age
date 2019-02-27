#include <age/entity/EntityEvent.h>

#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>

using namespace age::entity;

class EntityEvent::Impl
{
public:
	Impl(const Entity& e, Type t) : entity{e}, type{t}
	{
	}

	const Entity& entity;
	Type type;
};

EntityEvent::EntityEvent(const Entity& e, Type t) : Event(), pimpl(e, t)
{
}
EntityEvent::~EntityEvent()
{
}

const Entity& EntityEvent::getEntity() const
{
	return this->pimpl->entity;
}

EntityEvent::Type EntityEvent::getType() const
{
	return this->pimpl->type;
}

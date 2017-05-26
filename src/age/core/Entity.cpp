#include <age/core/Entity.h>
#include <age/core/PimplImpl.h>

using namespace age::core;

namespace
{
	uint32_t UniqueID = 0;
}

class Entity::Impl
{
public:
	Impl() : id{++UniqueID}
	{
	}

	uint32_t id;
};

Entity::Entity() : Object(), pimpl()
{
}

Entity::~Entity()
{
}

uint32_t Entity::getID()
{
	return this->pimpl->id;
}

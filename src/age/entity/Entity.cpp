#include <age/entity/Entity.h>

using namespace age::entity;

namespace
{
	size_t UniqueID = 0;
}

Entity::Entity() : id{++UniqueID}
{
}

Entity::~Entity()
{
}

size_t Entity::getID()
{
	return this->id;
}

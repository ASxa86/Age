#include <age/entity/Entity.h>
#include <age/entity/EntityManager.h>

using namespace age::entity;

Entity::Entity() : id{-1}, manager{nullptr}
{
}

Entity::Entity(const Entity&& x) noexcept : id{x.id}, manager{x.manager}
{
}

int Entity::getID() const
{
	return this->id;
}

bool Entity::valid() const
{
	return (this->manager != nullptr) && (this->manager->valid(this) == true);
}

void Entity::destroy() const
{
	if(this->manager != nullptr)
	{
		this->manager->destroy(this);
	}
}

bool Entity::operator==(const Entity& x) const
{
	return this->id == x.id;
}

bool Entity::operator!=(const Entity& x) const
{
	return !(*this == x);
}

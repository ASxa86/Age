#include <age/entity/Entity.h>
#include <age/entity/EntityManager.h>

using namespace age::entity;

Entity::Entity() : id{0}, manager{nullptr}
{
}
int Entity::getID() const
{
	return this->id;
}

bool Entity::valid() const
{
	return (this->manager != nullptr) && (this->manager->valid(*this) == true);
}

void Entity::destroy() const
{
	if(this->manager != nullptr)
	{
		this->manager->destroy(*this);
	}
}

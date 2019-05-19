#include <age/entity/Entity.h>
#include <age/entity/EntityManager.h>

using namespace age::entity;

Entity::Entity() : id{-1}, manager{nullptr}
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

bool Entity::operator==(const Entity& x) const
{
	return this->id == x.id;
}

bool Entity::operator!=(const Entity& x) const
{
	return !(*this == x);
}

std::vector<Component*> Entity::getComponents() const
{
	std::vector<Component*> v;

	const auto& pools = this->manager->getPools();

	for(const auto& [type, pool] : pools)
	{
		if(pool->test(this->id) == true)
		{
			const auto c = pool->component(this->id);

			if(c != nullptr)
			{
				v.push_back(c);
			}
		}
	}

	return v;
}

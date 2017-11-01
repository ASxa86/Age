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

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::create()
{
	Entity e{};
	e.manager = this;

	if(this->indexList.empty() == true)
	{
		e.id = static_cast<int>(this->entities.size());
		this->entities.push_back(e);
		this->validEntities.push_back(true);
	}
	else
	{
		e.id = this->indexList.back();
		this->indexList.pop_back();
		this->validEntities[e.id] = true;
	}

	if(e.id >= this->componentMasks.size())
	{
		this->componentMasks.resize(e.id + 1);
	}

	for(const auto& pool : this->pools)
	{
		if(e.id >= pool->size())
		{
			pool->resize(e.id + 1);
		}
	}

	return e;
}

void EntityManager::destroy(Entity x)
{
	if(x.valid() == true)
	{
		this->indexList.push_back(x.id);
		this->validEntities[x.id] = false;
		this->componentMasks[x.id].reset();
	}
}

bool EntityManager::valid(Entity x) const
{
	return (x.id < this->validEntities.size()) && (this->validEntities[x.id] == true);
}

const std::vector<Entity>& EntityManager::getEntities() const
{
	return this->entities;
}

#include <age/entity/EntityManager.h>

using namespace age::entity;

Entity::Entity() : id{0}, manager{nullptr}
{
}

bool Entity::valid() const
{
	return this->manager != nullptr && this->id < this->manager->entities.size();
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
	}
	else
	{
		e.id = this->indexList.back();
		this->indexList.pop_back();
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
		this->entities[x.id].manager = nullptr;
		this->indexList.push_back(x.id);
	}
}

const std::vector<Entity>& EntityManager::getEntities() const
{
	return this->entities;
}

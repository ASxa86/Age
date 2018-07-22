#include <age/entity/EntityManager.h>
#include <algorithm>
#include <numeric>

using namespace age::core;
using namespace age::entity;

EntityManager::EntityManager(std::size_t x) : count{x}, validEntities{new bool[x]}
{
	// Initialize with valid entity IDs.
	this->indexList.resize(this->count);
	this->entities.resize(this->count, Entity());

	// Populate a list of valid entity ids in order to quickly assign and manage
	// available ids during entity creation.
	std::iota(std::rbegin(this->indexList), std::rend(this->indexList), 0);
	std::memset(this->validEntities, false, this->count);
}

EntityManager::~EntityManager()
{
	delete[] this->validEntities;
}

Entity EntityManager::create()
{
	Entity e;

	if(this->indexList.empty() == false)
	{
		e.id = this->indexList.back();
		e.manager = this;
		this->indexList.pop_back();
		this->entities[e.id] = e;
		this->validEntities[e.id] = true;

		EventQueue::Instance().sendEvent(std::make_unique<EntityEvent>(e, EntityEvent::Type::EntityAdded));
	}

	return e;
}

void EntityManager::destroy(Entity x)
{
	if(this->validEntities[x.id] == true)
	{
		this->indexList.push_back(x.id);
		this->validEntities[x.id] = false;
		this->entities[x.id].id = -1;
		this->entities[x.id].manager = nullptr;

		for(auto& pool : this->pools)
		{
			if(pool.second->test(x.id) == true)
			{
				pool.second->destroy(x.id);
			}
		}

		EventQueue::Instance().sendEvent(std::make_unique<EntityEvent>(x, EntityEvent::Type::EntityRemoved));
	}
}

bool EntityManager::valid(Entity x) const
{
	return this->validEntities[x.id];
}

const std::vector<Entity>& EntityManager::getEntities() const
{
	return this->entities;
}

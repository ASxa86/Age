#include <age/entity/EntityManager.h>

using namespace age::core;
using namespace age::entity;

EntityManager::EntityManager()
{
}

EntityManager::EntityManager(size_t reserve)
{
	this->entities.reserve(reserve);
	for(auto i = 0; i < reserve; ++i)
	{
		Entity e;
		e.manager = this;
		e.id = static_cast<int>(this->entities.size());
		this->entities.push_back(Entity());
	}
}

EntityManager::~EntityManager()
{
}

Entity EntityManager::create()
{
	Entity e;
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

	for(const auto& pair : this->pools)
	{
		pair.second->allocate();
	}

	EventQueue::Instance().sendEvent(std::make_unique<EntityEvent>(e, EntityEvent::Type::EntityAdded));

	return e;
}

void EntityManager::destroy(Entity x)
{
	if(x.valid() == true)
	{
		this->indexList.push_back(x.id);
		this->validEntities[x.id] = false;

		EventQueue::Instance().sendEvent(std::make_unique<EntityEvent>(x, EntityEvent::Type::EntityRemoved));
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

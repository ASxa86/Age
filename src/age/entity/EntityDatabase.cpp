#include <age/core/EventQueue.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/EntityEvent.h>

using namespace age::entity;

bool EntityDatabase::addEntity(std::unique_ptr<Entity> x)
{
	auto evt = std::make_unique<EntityEvent>(x.get(), EntityEvent::Type::EntityAdded);
	age::core::EventQueue::Instance().sendEvent(std::move(evt));
	return this->addChild(std::move(x));
}

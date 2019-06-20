#include <age/core/EventQueue.h>
#include <age/entity/Component.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityEvent.h>

using namespace age::entity;

Entity::Entity()
{
}

bool Entity::addComponent(std::unique_ptr<Component> x)
{
	auto evt = std::make_unique<EntityEvent>(this, EntityEvent::Type::ComponentAdded);
	evt->Component = x.get();
	age::core::EventQueue::Instance().sendEvent(std::move(evt));
	return this->addChild(std::move(x));
}

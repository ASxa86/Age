#include <azule/core/EventQueue.h>
#include <azule/entity/Component.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityEvent.h>

using namespace azule;

Entity::Entity()
{
}

bool Entity::addComponent(std::unique_ptr<Component> x)
{
	auto evt = std::make_unique<EntityEvent>(this, EntityEvent::Type::ComponentAdded);
	evt->Component = x.get();
	azule::EventQueue::Instance().sendEvent(std::move(evt));
	return this->addChild(std::move(x));
}

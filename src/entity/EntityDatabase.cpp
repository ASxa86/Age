#include <azule/core/EventQueue.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/EntityEvent.h>

using namespace azule;

bool EntityDatabase::addEntity(std::unique_ptr<Entity> x)
{
	if(x != nullptr)
	{
		auto evt = std::make_unique<EntityEvent>(x.get(), EntityEvent::Type::EntityAdded);
		azule::EventQueue::Instance().sendEvent(std::move(evt));
		return this->addChild(std::move(x));
	}

	return false;
}

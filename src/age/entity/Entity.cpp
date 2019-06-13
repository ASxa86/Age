#include <age/entity/Component.h>
#include <age/entity/Entity.h>

using namespace age::entity;

Entity::Entity()
{
}

bool Entity::addComponent(std::unique_ptr<Component> x)
{
	return this->addChild(std::move(x));
}

#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>

using namespace age::entity;

bool EntityDatabase::addEntity(std::unique_ptr<Entity> x)
{
	return this->addChild(std::move(x));
}

#include <age/core/System.h>
#include <age/core/Engine.h>
#include <age/core/Entity.h>

using namespace age::core;

System::System() : Object()
{
}

System::~System()
{
}

std::vector<std::shared_ptr<Entity>> System::getEntities() const
{
	return this->getParent<Engine>()->getChildren<Entity>();
}

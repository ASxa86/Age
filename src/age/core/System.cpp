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

void System::initialize()
{
}

std::vector<Entity*> System::getEntities() const
{
	return this->getParent<Engine>()->getChildren<Entity>();
}

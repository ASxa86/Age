#include <age/core/System.h>
#include <age/core/Engine.h>
#include <age/core/Entity.h>

using namespace age::core;

System::System()
{
}

System::~System()
{
}

std::vector<Entity*> System::getEntities() const
{
	return this->getParent<Engine>()->getChildren<Entity>();
}

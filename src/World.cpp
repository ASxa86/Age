#include <azule/World.h>

#include <azule/Entity.h>

using namespace azule;

Entity World::create()
{
	return Entity(this->registry.create(), this);
}

#include <age/physics/CircleCollisionComponent.h>

using namespace age::physics;

CircleCollisionComponent::CircleCollisionComponent() : CollisionComponent()
{
	this->addProperty(this->Radius, "Radius");
}

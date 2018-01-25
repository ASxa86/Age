#include <age/physics/CollisionSystem.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/math/TransformComponent.h>

using namespace age::core;
using namespace age::math;
using namespace age::physics;

CollisionSystem::CollisionSystem() : age::entity::System()
{
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::frame(std::chrono::microseconds)
{
}

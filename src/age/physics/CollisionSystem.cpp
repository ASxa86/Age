#include <age/physics/CollisionSystem.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/math/TransformComponent.h>
#include <age/core/Entity.h>

using namespace age::core;
using namespace age::math;
using namespace age::physics;

CollisionSystem::CollisionSystem() : FixedSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::frame(std::chrono::microseconds)
{
}

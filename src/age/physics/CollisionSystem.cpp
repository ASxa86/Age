#include <age/physics/CollisionSystem.h>
#include <age/physics/BoxCollisionComponent.h>
#include <age/math/TransformComponent.h>

using namespace age::core;
using namespace age::math;
using namespace age::physics;

CollisionSystem::CollisionSystem() : FixedSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::frame(const std::vector<age::entity::Entity>&, std::chrono::microseconds)
{
}

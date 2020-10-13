#include <azule/Entity.h>

using namespace azule;

Entity::Entity(entt::entity h, World* w) : handle{h}, world{w}
{
}

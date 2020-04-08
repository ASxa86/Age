#include <age/graphics/RenderSystem.h>

#include <age/core/Configuration.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/TransformComponent.h>
#include <age/graphics/DrawableComponent.h>
#include <age/utilities/PimplImpl.h>
#include <SFML/Graphics.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;
using namespace age::math;

using namespace age::graphics;

namespace
{
	sf::Vector2f FromVector(const age::math::Vector& x)
	{
		return {static_cast<float>(x.X), static_cast<float>(x.Y)};
	}
}

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::render(sf::RenderTarget& target, std::chrono::microseconds states)
{
	const auto manager = this->getEntityDatabase();

	for(auto entity : manager->getChildren<Entity>())
	{
		auto d = entity->getChild<DrawableComponent>();
		auto t = entity->getChild<TransformComponent>();

		if(d != nullptr)
		{
			if(d->Enabled == true)
			{
				sf::RenderStates states;
				states.transform.translate(FromVector(t->Position)).rotate(static_cast<float>(t->Rotation));
				target.draw(d->getDrawable(), states);
			}
		}
	}
}

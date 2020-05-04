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

void RenderSystem::render(sf::RenderTarget& target, std::chrono::microseconds x)
{
	const auto manager = this->getEntityDatabase();

	std::vector<DrawableComponent*> drawables;

	for(auto entity : manager->getChildren<Entity>())
	{
		for(auto drawable : entity->getChildren<DrawableComponent>())
		{
			drawables.push_back(drawable);
		}
	}

	// Render all drawables based on their render order.
	std::sort(std::begin(drawables), std::end(drawables), [](auto& a, auto& b) { return a->RenderOrder < b->RenderOrder; });

	for(auto d : drawables)
	{
		auto entity = d->getParent<Entity>();
		auto t = entity->getChild<TransformComponent>();

		sf::RenderStates states;

		if(t != nullptr)
		{
			if(d->UsePosition == true)
			{
				states.transform.translate(FromVector(t->Position));
			}

			if(d->UseRotation == true)
			{
				states.transform.rotate(static_cast<float>(t->Rotation));
			}
		}

		if(d->Enabled == true && d->getDrawable() != nullptr)
		{
			target.draw(*d->getDrawable(), states);
		}
	}
}

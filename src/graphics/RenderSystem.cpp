#include <azule/graphics/RenderSystem.h>

#include <azule/core/Configuration.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <azule/graphics/DrawableComponent.h>
#include <azule/utilities/PimplImpl.h>
#include <SFML/Graphics.hpp>

using namespace azule;
using namespace azule;
using namespace azule;
using namespace azule;

using namespace azule;

namespace
{
	sf::Vector2f FromVector(const glm::vec2& x)
	{
		return {static_cast<float>(x.x), static_cast<float>(x.y)};
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

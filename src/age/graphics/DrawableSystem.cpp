#include <age/graphics/DrawableSystem.h>

#include <age/core/Configuration.h>
#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/TransformComponent.h>
#include <age/graphics/BoxSelectionComponent.h>
#include <age/graphics/SpriteComponent.h>
#include <SFML/Graphics.hpp>

using namespace age::core;
using namespace age::entity;
using namespace age::graphics;
using namespace age::math;

namespace
{
	sf::Vector2f FromVector(const age::math::Vector& x)
	{
		return {static_cast<float>(x.X), static_cast<float>(x.Y)};
	}

	sf::Color FromColor(const std::array<int, 4>& x)
	{
		return sf::Color{static_cast<sf::Uint8>(x[0]), static_cast<sf::Uint8>(x[1]), static_cast<sf::Uint8>(x[2]), static_cast<sf::Uint8>(x[3])};
	}
}

struct DrawableSystem::Impl
{
	sf::RenderStates state;
};

DrawableSystem::DrawableSystem()
{
	const auto factor = static_cast<float>(Configuration::Instance().getPixelsPerMeter());
	this->pimpl->state.transform.scale(factor, factor);
}

DrawableSystem::~DrawableSystem()
{
}

void DrawableSystem::render(sf::RenderTarget& target, std::chrono::microseconds /*x*/)
{
	const auto manager = this->getEntityDatabase();

	for(auto entity : manager->getChildren<Entity>())
	{
		auto s = entity->getChild<SpriteComponent>();
		auto t = entity->getChild<TransformComponent>();

		if(s != nullptr)
		{
			auto& sprite = s->getSprite();
			sprite.setRotation(static_cast<float>(s->Rotation));

			if(t != nullptr)
			{
				sprite.setPosition(FromVector(t->Position));
				sprite.setRotation(sprite.getRotation() + static_cast<float>(t->Rotation));
			}

			target.draw(sprite);
		}

		auto bSelect = entity->getChild<BoxSelectionComponent>();

		if(bSelect != nullptr && bSelect->Selected == true)
		{
			auto& shape = bSelect->Shape;
			shape.setFillColor(FromColor(bSelect->FillColor));
			shape.setOutlineColor(FromColor(bSelect->OutlineColor));
			shape.setOutlineThickness(static_cast<float>(bSelect->OutlineThickness));
			shape.setSize(FromVector(bSelect->Size));

			if(t != nullptr)
			{
				shape.setPosition(FromVector(t->Position));
				shape.setRotation(static_cast<float>(t->Rotation));
			}

			target.draw(shape);
		}
	}
}

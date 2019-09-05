#include <age/graphics/HealthBarSystem.h>

#include <age/core/Configuration.h>
#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/HealthComponent.h>
#include <age/entity/TransformComponent.h>
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

struct HealthBarSystem::Impl
{
	sf::RenderStates state;
};

HealthBarSystem::HealthBarSystem()
{
	this->addProperty(this->Color, "Color");
	this->addProperty(this->Size, "Size");
	this->addProperty(this->Offset, "Offset");

	const auto factor = static_cast<float>(Configuration::Instance().getPixelsPerMeter());
	this->pimpl->state.transform.scale(factor, factor);
}

HealthBarSystem::~HealthBarSystem()
{
}

void HealthBarSystem::render(sf::RenderTarget& target, std::chrono::microseconds /*x*/)
{
	const auto manager = this->getEntityDatabase();

	for(auto entity : manager->getChildren<Entity>())
	{
		auto h = entity->getChild<HealthComponent>();
		auto t = entity->getChild<TransformComponent>();

		if(h != nullptr)
		{
			sf::RectangleShape healthbar;
			healthbar.setSize(FromVector(this->Size));
			healthbar.setFillColor(FromColor(this->Color));
			healthbar.setPosition(FromVector(this->Offset + t->Position));

			sf::RectangleShape outline = healthbar;
			outline.setFillColor(sf::Color::Transparent);
			outline.setOutlineColor(sf::Color::Black);
			outline.setOutlineThickness(1.0f);

			auto size = healthbar.getSize();
			size.x *= static_cast<float>(h->getPercentage());
			healthbar.setSize(size);

			target.draw(healthbar);
			target.draw(outline);
		}
	}
}

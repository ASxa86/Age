#include <age/graphics/TextSystem.h>

#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>
#include <age/entity/TransformComponent.h>
#include <SFML/Graphics.hpp>

using namespace age::entity;
using namespace age::graphics;
using namespace age::math;

namespace
{
	sf::Vector2f FromVector(const age::math::Vector& x)
	{
		return {static_cast<float>(x.X), static_cast<float>(x.Y)};
	}
}

TextSystem::TextSystem()
{
}

TextSystem::~TextSystem()
{
}

void TextSystem::render(sf::RenderTarget& target, std::chrono::microseconds /*x*/)
{
	const auto manager = this->getEntityManager();

	manager->each<TransformComponent, std::shared_ptr<sf::Text>>([&target, this](Entity&, TransformComponent& t, std::shared_ptr<sf::Text>& d) {
		auto transform = dynamic_cast<sf::Transformable*>(d.get());

		if(transform != nullptr)
		{
			transform->setPosition(FromVector(t.Position));
		}

		target.draw(*d);
	});
}

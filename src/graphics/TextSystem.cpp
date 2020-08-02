#include <azule/graphics/TextSystem.h>

#include <azule/utilities/PimplImpl.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <SFML/Graphics.hpp>

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

TextSystem::TextSystem()
{
}

TextSystem::~TextSystem()
{
}

void TextSystem::render(sf::RenderTarget& /*target*/, std::chrono::microseconds /*x*/)
{
	// const auto manager = this->getEntityDatabase();

	// manager->each<TransformComponent, std::shared_ptr<sf::Text>>([&target, this](Entity&, TransformComponent& t, std::shared_ptr<sf::Text>& d) {
	//	auto transform = dynamic_cast<sf::Transformable*>(d.get());

	//	if(transform != nullptr)
	//	{
	//		transform->setPosition(FromVector(t.Position));
	//	}

	//	target.draw(*d);
	//});
}

#include <age/graphics/DrawableComponent.h>
#include <age/math/TransformComponent.h>
#include <SFML/Graphics/Transformable.hpp>

using namespace age::core;
using namespace age::graphics;
using namespace age::math;

DrawableComponent::DrawableComponent() : age::core::Object()
{
}

DrawableComponent::~DrawableComponent()
{
}

void DrawableComponent::updateTransform(sf::Transformable& x)
{
	const auto entity = this->getParent();
	const auto transform = entity->getChild<TransformComponent>();

	const auto pos = transform->getPosition();
	const auto rotation = transform->getRotation();

	x.setPosition(Vector::To<sf::Vector2f, float>(pos));
	x.setRotation(static_cast<float>(rotation));
}

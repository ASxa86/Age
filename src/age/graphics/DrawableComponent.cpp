#include <age/graphics/DrawableComponent.h>
#include <age/math/TransformComponent.h>
#include <SFML/Graphics/Transformable.hpp>
#include <boost/qvm/vec_access.hpp>
#include <boost/qvm/vec_operations.hpp>

using namespace age::core;
using namespace age::graphics;
using namespace age::math;
using namespace boost::qvm;

DrawableComponent::DrawableComponent() : age::core::Object()
{
}

DrawableComponent::~DrawableComponent()
{
}

void DrawableComponent::updateTransform(sf::Transformable& x, unsigned int pixelsPerMeter)
{
	const auto entity = this->getParent();
	const auto transform = entity->getChild<TransformComponent>();

	const auto pos = transform->getPosition() * pixelsPerMeter;
	const auto rotation = transform->getRotation();

	x.setPosition({static_cast<float>(X(pos)), static_cast<float>(Y(pos))});
	x.setRotation(static_cast<float>(rotation));
}

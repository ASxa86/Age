#include <azule/graphics/DrawableComponent.h>

using namespace azule;

DrawableComponent::DrawableComponent()
{
	this->addProperty("RenderOrder", this->RenderOrder);
	this->addProperty("UseRotation", this->UseRotation);
	this->addProperty("UsePosition", this->UsePosition);
}

const sf::Drawable* DrawableComponent::getDrawable()
{
	return nullptr;
}

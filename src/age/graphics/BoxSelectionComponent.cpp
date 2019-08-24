#include <age/graphics/BoxSelectionComponent.h>

using namespace age::graphics;

BoxSelectionComponent::BoxSelectionComponent()
{
	this->addProperty(this->Size, "Size");
	this->addProperty(this->OutlineThickness, "OutlineThickness");
	this->addProperty(this->OutlineColor, "OutlineColor");
	this->addProperty(this->FillColor, "FillColor");
}

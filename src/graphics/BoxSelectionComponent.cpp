#include <azule/graphics/BoxSelectionComponent.h>

using namespace azule;

BoxSelectionComponent::BoxSelectionComponent()
{
	this->addProperty("Size", this->Size);
	this->addProperty("FillColor", this->FillColor);
	this->addProperty("OutlineColor", this->OutlineColor);
	this->addProperty("OutlineThickness", this->OutlineThickness);
}

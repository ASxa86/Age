#include <azule/entity/SelectionComponent.h>

using namespace azule;

SelectionComponent::SelectionComponent()
{
	this->addProperty("Selected", this->Selected);
}

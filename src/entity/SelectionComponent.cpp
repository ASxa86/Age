#include <age/entity/SelectionComponent.h>

using namespace age::entity;

SelectionComponent::SelectionComponent()
{
	this->addProperty(this->Selected, "Selected");
}

#include <age/entity/HealthComponent.h>

using namespace age::entity;

HealthComponent::HealthComponent()
{
	this->addProperty(this->Health, "Health");
	this->addProperty(this->HealthMax, "HealthMax");
}

double HealthComponent::getPercentage() const
{
	return static_cast<double>(this->Health) / static_cast<double>(this->HealthMax);
}

#include <age/entity/HealthComponent.h>

using namespace age::entity;

HealthComponent::HealthComponent()
{
}

double HealthComponent::getPercentage() const
{
	return static_cast<double>(this->Health) / static_cast<double>(this->HealthMax);
}

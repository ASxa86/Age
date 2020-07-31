#include <PaddleAIComponent.h>
#include <azule/entity/Entity.h>

using namespace azule;
using namespace azule::pong;

PaddleAIComponent::PaddleAIComponent() : ball{}
{
}

PaddleAIComponent::~PaddleAIComponent()
{
}

void PaddleAIComponent::setBall(Entity /*x*/)
{
	// this->ball = x;
}

const Entity& PaddleAIComponent::getBall() const
{
	return this->ball;
}

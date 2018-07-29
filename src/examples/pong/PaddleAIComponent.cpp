#include <examples/pong/PaddleAIComponent.h>

#include <age/entity/Entity.h>

using namespace age::entity;
using namespace age::pong;

PaddleAIComponent::PaddleAIComponent() : ball{nullptr}
{
}

PaddleAIComponent::~PaddleAIComponent()
{
}

void PaddleAIComponent::setBall(Entity* x)
{
	this->ball = x;
}

Entity* PaddleAIComponent::getBall() const
{
	return this->ball;
}

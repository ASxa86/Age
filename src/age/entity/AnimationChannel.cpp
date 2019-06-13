#include <age/entity/AnimationChannel.h>

using namespace age::entity;

Channel::Channel(Shape s) : shape{s}
{
}

Channel::~Channel()
{
}

Channel::Shape Channel::getShape() const
{
	return this->shape;
}

void Channel::evaluate(std::chrono::microseconds) const
{
}

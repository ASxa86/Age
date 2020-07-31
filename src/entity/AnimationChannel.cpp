#include <azule/entity/AnimationChannel.h>

using namespace azule;

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

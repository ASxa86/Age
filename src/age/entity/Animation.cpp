#include <age/entity/Animation.h>

using namespace age::entity;

Animation::Animation() : channels{}
{
}

Animation::Animation(Animation&& x) : channels{std::move(x.channels)}
{
}

Animation::~Animation()
{
}

void Animation::process(std::chrono::microseconds x) const
{
	for(const auto& channel : this->channels)
	{
		channel->evaluate(x);
	}
}

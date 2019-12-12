#include <age/entity/Animation.h>

using namespace age::entity;

Animation::Animation() : channels{}
{
}

void Animation::process(std::chrono::microseconds x) const
{
	for(const auto& channel : this->channels)
	{
		channel->evaluate(x);
	}
}

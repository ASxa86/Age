#include <azule/entity/AnimationComponent.h>

using namespace azule;

AnimationComponent::AnimationComponent() : currentAnimation{nullptr}, elapsed{0}, length{0}, speed{1.0}, isPlaying{false}
{
}

void AnimationComponent::play()
{
	this->isPlaying = true;
}

void AnimationComponent::stop()
{
	this->isPlaying = false;
}

void AnimationComponent::reset()
{
	this->setElapsed(std::chrono::microseconds::zero());

	if(this->currentAnimation != nullptr)
	{
		this->currentAnimation->process(this->getElapsed());
	}
}

bool AnimationComponent::getIsPlaying() const
{
	return this->isPlaying;
}

void AnimationComponent::setElapsed(std::chrono::microseconds x)
{
	this->elapsed = x;
}

std::chrono::microseconds AnimationComponent::getElapsed() const
{
	return this->elapsed;
}

void AnimationComponent::setSpeed(double x)
{
	this->speed = x;
}

double AnimationComponent::getSpeed() const
{
	return this->speed;
}

void AnimationComponent::setLength(std::chrono::microseconds x)
{
	this->length = x;
}

std::chrono::microseconds AnimationComponent::getLength() const
{
	return this->length;
}

void AnimationComponent::setCurrentAnimation(Animation* x)
{
	this->currentAnimation = x;
}

Animation* AnimationComponent::getCurrentAnimation() const
{
	return this->currentAnimation;
}

Animation* AnimationComponent::create()
{
	this->animations.push_back(Animation());
	return &this->animations.back();
}

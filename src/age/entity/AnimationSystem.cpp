#include <age/entity/AnimationSystem.h>

#include <age/core/Timer.h>
#include <age/entity/AnimationComponent.h>
#include <age/entity/EntityManager.h>

using namespace age::entity;

AnimationSystem::AnimationSystem() : System()
{
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::frame(std::chrono::microseconds x)
{
	const auto em = this->getEntityManager();

	em->each<AnimationComponent>([x](auto&, AnimationComponent& a) {
		const auto animation = a.getCurrentAnimation();

		if(a.getIsPlaying() == true && animation != nullptr)
		{
			const auto delta = age::core::seconds{std::chrono::duration_cast<age::core::seconds>(x).count() * a.getSpeed()};
			a.setElapsed(a.getElapsed() + std::chrono::duration_cast<std::chrono::microseconds>(delta));

			if(a.getElapsed() > a.getLength())
			{
				a.setElapsed(a.getLength());
			}

			animation->process(a.getElapsed());

			if(a.getElapsed() >= a.getLength())
			{
				a.setElapsed(std::chrono::microseconds::zero());
			}
		}
	});
}

#include <examples/pong/Ball.h>

#include <age/math/TransformComponent.h>
#include <age/graphics/CircleComponent.h>
#include <age/physics/KinematicComponent.h>

using namespace age::core;
using namespace age::graphics;
using namespace age::math;
using namespace age::physics;
using namespace age::pong;

Ball::Ball()
{
	auto transform = std::make_unique<TransformComponent>();
	transform->setPosition({500.0, 500.0});

	auto circle = std::make_unique<CircleComponent>();
	circle->setRadius(10);

	auto kinematic = std::make_unique<KinematicComponent>();
	kinematic->setPosition(transform->getPosition());
	kinematic->setVelocity({50.0, 0.0});

	this->addChild(std::move(circle));
	this->addChild(std::move(transform));
	this->addChild(std::move(kinematic));
}

Ball::~Ball()
{
}

#include <examples/pong/Ball.h>

#include <age/core/TransformComponent.h>
#include <age/graphics/CircleComponent.h>
#include <age/physics/KinematicComponent.h>

using namespace age::core;
using namespace age::physics;
using namespace age::graphics;
using namespace age::pong;

Ball::Ball()
{
	this->addChild(std::make_unique<TransformComponent>());

	auto circle = std::make_unique<CircleComponent>();
	circle->setRadius(100.0);
	this->addChild(std::move(circle));

	auto kinematic = std::make_unique<KinematicComponent>();
	kinematic->setVelocity({50.0, 50.0});
	this->addChild(std::move(kinematic));
}

Ball::~Ball()
{
}

#include <examples/pong/Paddle.h>
#include <age/graphics/RectangleComponent.h>
// #include <age/graphics/TransformComponent.h>
// #include <age/graphics/GeometryComponent.h>

using namespace age::pong;

Paddle::Paddle() : Entity()
{
	auto rectangle = std::make_unique<age::graphics::RectangleComponent>();
	rectangle->setSize({100, 100});
	this->addChild(std::move(rectangle));
}

Paddle::~Paddle()
{
}

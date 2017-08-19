#include <age/math/TransformComponent.h>
#include <age/core/PimplImpl.h>
#include <boost/algorithm/clamp.hpp>

using namespace age::core;
using namespace age::math;
using namespace boost::algorithm;
using namespace boost::qvm;

class TransformComponent::Impl
{
public:
	Impl() :
		position{},
		rotation{}
	{
	}

	vec<double, 2> position;
	double rotation;
};

TransformComponent::TransformComponent()
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::setPosition(const vec<double, 2>& x)
{
	this->pimpl->position = x;
}

vec<double, 2> TransformComponent::getPosition() const
{
	return this->pimpl->position;
}

void TransformComponent::setRotation(double x)
{
	x = std::fmod(x, 360.0);
	if (x < 0.0) x += 360.0;
	this->pimpl->rotation = x;
}

double TransformComponent::getRotation() const
{
	return this->pimpl->rotation;
}

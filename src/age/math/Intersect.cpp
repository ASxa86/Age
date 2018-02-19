#include <age/math/Intersect.h>

#include <age/math/BoundingBox.h>
#include <age/math/BoundingCircle.h>

using namespace age::math;

bool age::math::intersect(const BoundingBox& a, const BoundingBox& b)
{
	const auto aleft = a.getLeft();
	const auto aright = a.getRight();
	const auto atop = a.getTop();
	const auto abottom = a.getBottom();

	const auto bleft = b.getLeft();
	const auto bright = b.getRight();
	const auto btop = b.getTop();
	const auto bbottom = b.getBottom();

	const auto leftIsBetweenLeftAndRight = aleft >= bleft && aleft <= bright;
	const auto rightIsBetweenLeftAndRight = aright <= bright && aright >= bleft;
	const auto topIsBetweenTopAndBottom = atop >= btop && atop <= bbottom;
	const auto bottomIsBetweenTopAndBotton = abottom <= bbottom && abottom >= btop;

	return (&a != &b)
		   && ((leftIsBetweenLeftAndRight == true && topIsBetweenTopAndBottom == true)
			   || (leftIsBetweenLeftAndRight == true && bottomIsBetweenTopAndBotton == true)
			   || (rightIsBetweenLeftAndRight == true && topIsBetweenTopAndBottom == true)
			   || (rightIsBetweenLeftAndRight == true && bottomIsBetweenTopAndBotton == true));
}

bool age::math::intersect(const BoundingCircle& a, const BoundingCircle& b)
{
	return (&a != &b) && ((a.getRadius() + b.getRadius()) >= age::math::distance(a.getPosition(), b.getPosition()));
}

bool age::math::intersect(const BoundingBox& a, const BoundingCircle& b)
{
	// https://yal.cc/rectangle-circle-intersection-test/
	const auto circlePos = b.getPosition();
	const auto deltaX = circlePos.getX() - std::max(a.getLeft(), std::min(circlePos.getX(), a.getRight()));
	const auto deltaY = circlePos.getY() - std::max(a.getTop(), std::min(circlePos.getY(), a.getBottom()));
	return (std::pow(deltaX, 2.0) + std::pow(deltaY, 2.0)) <= (std::pow(b.getRadius(), 2.0));
}

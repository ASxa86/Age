#include <age/core/Timer.h>
#include <age/utilities/PimplImpl.h>

using namespace age::core;

class Timer::Impl
{
public:
	Impl() : start{std::chrono::high_resolution_clock::now()}
	{
	}

	std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

Timer::Timer() : pimpl()
{
}

Timer::~Timer()
{
}

std::chrono::microseconds Timer::reset()
{
	const auto current = std::chrono::high_resolution_clock::now();
	const auto delta = current - this->pimpl->start;
	this->pimpl->start = current;
	return std::chrono::duration_cast<std::chrono::microseconds>(delta);
}

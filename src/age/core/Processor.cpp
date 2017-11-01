#include <age/core/Processor.h>
#include <age/core/PimplImpl.h>

using namespace age::core;

class Processor::Impl
{
public:
	std::vector<std::function<void(std::chrono::microseconds)>> fixedFunctions;
	std::vector<std::function<void(std::chrono::microseconds)>> variableFunctions;
	std::vector<std::function<void(std::chrono::microseconds)>> renderFunctions;
};

Processor::Processor()
{
}

Processor::~Processor()
{
}

void Processor::fixed(std::chrono::microseconds x)
{
	for(const auto& f : this->pimpl->fixedFunctions)
	{
		f(x);
	}
}

void Processor::variable(std::chrono::microseconds x)
{
	for(const auto& f : this->pimpl->variableFunctions)
	{
		f(x);
	}
}

void Processor::render(std::chrono::microseconds x)
{
	for(const auto& f : this->pimpl->renderFunctions)
	{
		f(x);
	}
}

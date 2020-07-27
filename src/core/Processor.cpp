#include <azule/core/Processor.h>
#include <azule/utilities/PimplImpl.h>

using namespace azule::core;

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

void Processor::addFixedFunction(const std::function<void(std::chrono::microseconds)>& x)
{
	this->pimpl->fixedFunctions.push_back(x);
}

void Processor::addVariableFunction(const std::function<void(std::chrono::microseconds)>& x)
{
	this->pimpl->variableFunctions.push_back(x);
}

void Processor::addRenderFunction(const std::function<void(std::chrono::microseconds)>& x)
{
	this->pimpl->renderFunctions.push_back(x);
}

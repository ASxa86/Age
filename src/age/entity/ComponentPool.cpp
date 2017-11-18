#include <age/entity/ComponentPool.h>

using namespace age::entity;

BasePool::BasePool()
{
}

BasePool::~BasePool()
{
}

void BasePool::setValid(std::size_t x, bool v)
{
	this->valid[x] = v;
}

bool BasePool::getValid(std::size_t x) const
{
	return this->valid[x];
}


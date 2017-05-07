#include <age/core/ChildEvent.h>

using namespace age::core;

ChildEvent::ChildEvent(Object* parent, Object* child) : Event(), parent{parent}, child{child}
{
}

ChildEvent::~ChildEvent()
{
}

Object* ChildEvent::getParent() const
{
	return this->parent;
}

Object* ChildEvent::getChild() const
{
	return this->child;
}

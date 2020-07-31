#include <azule/core/ChildEvent.h>

using namespace azule;

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

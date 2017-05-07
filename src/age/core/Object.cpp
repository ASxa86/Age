#include <age/core/Object.h>
#include <age/core/PimplImpl.h>

#include <algorithm>
#include <iostream>
using namespace age::core;

class Object::Impl
{
public:
	Impl() : children{}, id{}, parent{nullptr}
	{
	}

	std::vector<std::unique_ptr<Object>> children;
	std::string id;
	Object* parent;
};

Object::Object() : pimpl{}
{
}

Object::~Object()
{
}

void Object::setID(const std::string& x)
{
	this->pimpl->id = x;
}

std::string Object::getID() const
{
	return this->pimpl->id;
}

void Object::setParent(Object* x)
{
	this->pimpl->parent = x;
}

Object* Object::getParent() const
{
	return this->pimpl->parent;
}

bool Object::addChild(std::unique_ptr<Object> x)
{
	const auto foundIt = std::find_if(std::begin(this->pimpl->children), std::end(this->pimpl->children), [&x](const auto& up) { return x == up; });

	if(foundIt == std::end(this->pimpl->children))
	{
		x->pimpl->parent = this;
		this->pimpl->children.push_back(std::move(x));

		auto child = this->pimpl->children.back().get();

		return true;
	}

	return false;
}

Object* Object::getChild(size_t x)
{
	if(x < this->pimpl->children.size())
	{
		return this->pimpl->children[x].get();
	}

	return nullptr;
}

std::vector<Object*> Object::getChildren() const
{
	std::vector<Object*> v;
	v.reserve(this->pimpl->children.size());

	for(const auto& child : this->pimpl->children)
	{
		v.push_back(child.get());
	}

	return v;
}

bool Object::removeChild(Object* x)
{
	const auto removeIt =
		std::remove_if(std::begin(this->pimpl->children), std::end(this->pimpl->children), [x](const auto& up) { return x == up.get(); });

	if(removeIt != std::end(this->pimpl->children))
	{
		const auto child = std::move(*removeIt);
		this->pimpl->children.erase(removeIt, std::end(this->pimpl->children));
		return true;
	}

	return false;
}

bool Object::remove()
{
	if(this->pimpl->parent != nullptr)
	{
		return this->pimpl->parent->removeChild(this);
	}

	return false;
}

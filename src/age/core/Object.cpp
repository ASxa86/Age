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

	std::vector<std::shared_ptr<Object>> children;
	std::string id;
	Object* parent;
};

Object::Object() : pimpl()
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

void Object::initialize()
{
}

Object* Object::getParent() const
{
	return this->pimpl->parent;
}

bool Object::addChild(const std::shared_ptr<Object>& x)
{
	const auto foundIt = std::find(std::begin(this->pimpl->children), std::end(this->pimpl->children), x);

	if(foundIt == std::end(this->pimpl->children))
	{
		x->pimpl->parent = this;
		this->pimpl->children.push_back(x);

		return true;
	}

	return false;
}

std::shared_ptr<Object> Object::getChild(size_t x) const
{
	if(x < this->pimpl->children.size())
	{
		return this->pimpl->children[x];
	}

	return nullptr;
}

std::vector<std::shared_ptr<Object>> Object::getChildren(bool recursive) const
{
	std::vector<std::shared_ptr<Object>> v;
	v.reserve(this->pimpl->children.size());

	for(const auto& child : this->pimpl->children)
	{
		v.push_back(child);

		if(recursive == true)
		{
			const auto children = child->getChildren(recursive);
			v.insert(std::end(v), std::begin(children), std::end(children));
		}
	}

	return v;
}

bool Object::removeChild(const std::shared_ptr<Object>& x)
{
	const auto removeIt = std::remove(std::begin(this->pimpl->children), std::end(this->pimpl->children), x);

	if(removeIt != std::end(this->pimpl->children))
	{
		this->pimpl->children.erase(removeIt, std::end(this->pimpl->children));
		x->pimpl->parent = nullptr;
		return true;
	}

	return false;
}

bool Object::remove()
{
	const auto parent = this->getParent();

	if(parent != nullptr)
	{
		return parent->removeChild(this->shared_from_this());
	}

	return false;
}

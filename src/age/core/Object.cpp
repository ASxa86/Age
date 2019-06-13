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

bool Object::addChild(std::unique_ptr<Object> x)
{
	const auto foundIt = std::find(std::begin(this->pimpl->children), std::end(this->pimpl->children), x);

	if(foundIt == std::end(this->pimpl->children))
	{
		x->pimpl->parent = this;
		this->pimpl->children.push_back(std::move(x));

		return true;
	}

	return false;
}

Object* Object::getChild(size_t x) const
{
	if(x < this->pimpl->children.size())
	{
		return this->pimpl->children[x].get();
	}

	return nullptr;
}

std::vector<Object*> Object::getChildren(bool recursive) const
{
	std::vector<Object*> v;
	v.reserve(this->pimpl->children.size());

	for(const auto& child : this->pimpl->children)
	{
		v.push_back(child.get());

		if(recursive == true)
		{
			const auto children = child->getChildren(recursive);
			v.insert(std::end(v), std::begin(children), std::end(children));
		}
	}

	return v;
}

std::unique_ptr<Object> Object::remove()
{
	const auto parent = this->getParent();

	if(parent != nullptr)
	{
		const auto begin = std::begin(parent->pimpl->children);
		const auto end = std::end(parent->pimpl->children);

		const auto removeIt = std::remove_if(begin, end, [this](auto& x) { return this == x.get(); });

		if(removeIt != end)
		{
			auto ptr = std::move(*removeIt);
			parent->pimpl->children.erase(removeIt, end);
			this->pimpl->parent = nullptr;
			return ptr;
		}
	}

	return nullptr;
}

#include <age/core/Object.h>
#include <algorithm>
#include <iostream>

using namespace age::core;
using namespace age::utilities;

Object::Object()
{
}

Object::~Object()
{
}

void Object::setID(const std::string& x)
{
	this->id = x;
}

std::string Object::getID() const
{
	return this->id;
}

void Object::startup()
{
	if(this->status < Status::Startup)
	{
		for(auto& child : this->children)
		{
			child->startup();
		}

		this->onStartup();

		this->status = Status::Startup;
	}
}

void Object::shutdown()
{
	if(this->status < Status::Shutdown)
	{
		for(auto& child : this->children)
		{
			child->shutdown();
		}

		this->onShutdown();

		this->status = Status::Shutdown;
	}
}

Object* Object::getParent() const
{
	return this->parent;
}

bool Object::addChild(std::unique_ptr<Object> x)
{
	if(x != nullptr)
	{
		const auto foundIt = std::find(std::begin(this->children), std::end(this->children), x);

		if(foundIt == std::end(this->children))
		{
			x->parent = this;
			this->children.push_back(std::move(x));
			this->children.back()->startup();
			this->onAddChild(this->children.back().get());

			return true;
		}
	}

	return false;
}

Object* Object::getChild(size_t x) const
{
	if(x < this->children.size())
	{
		return this->children[x].get();
	}

	return nullptr;
}

std::vector<Object*> Object::getChildren(FindOption option) const
{
	std::vector<Object*> v;
	v.reserve(this->children.size());

	for(const auto& child : this->children)
	{
		v.push_back(child.get());

		if(option == FindOption::Recursive)
		{
			const auto children = child->getChildren(option);
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
		const auto begin = std::begin(parent->children);
		const auto end = std::end(parent->children);

		const auto removeIt = std::remove_if(begin, end, [this](auto& x) { return this == x.get(); });

		if(removeIt != end)
		{
			auto ptr = std::move(*removeIt);
			this->onRemoveChild(ptr.get());
			parent->children.erase(removeIt, end);
			this->parent = nullptr;
			return ptr;
		}
	}

	return nullptr;
}

ScopedConnection Object::addOnAddChild(std::function<void(Object*)> x)
{
	return this->onAddChild.connect_scoped(x);
}

ScopedConnection Object::addOnRemoveChild(std::function<void(Object*)> x)
{
	return this->onRemoveChild.connect_scoped(x);
}

void Object::track(ScopedConnection x)
{
	this->connection.emplace_back(std::move(x));
}

void Object::onStartup()
{
}

void Object::onShutdown()
{
}

#include <age/core/Object.h>
#include <age/utilities/PimplImpl.h>
#include <age/utilities/Signal.h>
#include <algorithm>
#include <iostream>

using namespace age::core;
using namespace age::utilities;

class Object::Impl
{
public:
	std::vector<std::unique_ptr<Object>> children;
	std::vector<ScopedConnection> connection;
	Signal<Object*> onAddChild;
	Signal<Object*> onRemoveChild;
	std::string id;
	Object* parent{nullptr};
	Status status{Status::None};
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

void Object::startup()
{
	if(this->pimpl->status < Status::Startup)
	{
		for(auto& child : this->pimpl->children)
		{
			child->startup();
		}

		this->onStartup();

		this->pimpl->status = Status::Startup;
	}
}

void Object::shutdown()
{
	if(this->pimpl->status < Status::Shutdown)
	{
		for(auto& child : this->pimpl->children)
		{
			child->shutdown();
		}

		this->onShutdown();

		this->pimpl->status = Status::Shutdown;
	}
}

Object* Object::getParent() const
{
	return this->pimpl->parent;
}

bool Object::addChild(std::unique_ptr<Object> x)
{
	if(x != nullptr)
	{
		const auto foundIt = std::find(std::begin(this->pimpl->children), std::end(this->pimpl->children), x);

		if(foundIt == std::end(this->pimpl->children))
		{
			x->pimpl->parent = this;
			this->pimpl->children.push_back(std::move(x));
			this->pimpl->children.back()->startup();
			this->pimpl->onAddChild(this->pimpl->children.back().get());

			return true;
		}
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

std::vector<Object*> Object::getChildren(FindOption option) const
{
	std::vector<Object*> v;
	v.reserve(this->pimpl->children.size());

	for(const auto& child : this->pimpl->children)
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
		const auto begin = std::begin(parent->pimpl->children);
		const auto end = std::end(parent->pimpl->children);

		const auto removeIt = std::remove_if(begin, end, [this](auto& x) { return this == x.get(); });

		if(removeIt != end)
		{
			auto ptr = std::move(*removeIt);
			this->pimpl->onRemoveChild(ptr.get());
			parent->pimpl->children.erase(removeIt, end);
			this->pimpl->parent = nullptr;
			return ptr;
		}
	}

	return nullptr;
}

ScopedConnection Object::addOnAddChild(std::function<void(Object*)> x)
{
	return this->pimpl->onAddChild.connect_scoped(x);
}

ScopedConnection Object::addOnRemoveChild(std::function<void(Object*)> x)
{
	return this->pimpl->onRemoveChild.connect_scoped(x);
}

void Object::track(ScopedConnection x)
{
	this->pimpl->connection.emplace_back(std::move(x));
}

void Object::onStartup()
{
}

void Object::onShutdown()
{
}

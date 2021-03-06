#pragma once

#include <azule/export.hxx>
#include <azule/reflection/Properties.h>
#include <azule/utilities/Signal.h>
#include <functional>
#include <string>
#include <vector>

namespace azule
{
	///
	///	\class Object
	///
	///	\brief Base class for all objects of azule. Designed using the composite pattern from the GoF.
	///
	///	\date April 22, 2017
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT Object : public Properties, public std::enable_shared_from_this<Object>
	{
	public:
		enum class FindOption : int
		{
			Direct,
			Recursive
		};

		enum class Status : int
		{
			None,
			Startup,
			Shutdown
		};

		Object();
		virtual ~Object();

		///
		///	Set an identifier for this object.
		///
		void setID(const std::string& x);

		///
		///	Get this object's identifier.
		///
		std::string getID() const;

		///
		///
		///
		void startup();

		///
		///
		///
		void shutdown();

		///
		///	Gets the parent for this object.
		///
		std::shared_ptr<Object> getParent() const;

		///
		///	Return the parent as type T. Returns nullptr if the parent is not of type T.
		///
		///	\param recursive Recursively search for a parent of the given type T.
		///
		template <typename T>
		std::shared_ptr<T> getParent(FindOption option = FindOption::Direct) const
		{
			const auto parent = this->getParent();
			auto parentType = std::dynamic_pointer_cast<T>(parent);

			if(option == FindOption::Recursive)
			{
				if(parent != nullptr && parentType == nullptr)
				{
					parentType = parent->getParent<T>(option);
				}
			}

			return parentType;
		}

		///
		///	Add an object as a child of this object.
		///
		///	Ownership of the object will be transfered to this object.
		///
		virtual bool addChild(std::shared_ptr<Object> x);

		///
		///	Return the child with the given index. Default 0.
		///
		virtual std::shared_ptr<Object> getChild(size_t x = 0) const;

		///
		///	Return the child of type T with the given index. Default 0.
		///
		template <typename T>
		auto getChild(size_t x = 0) const
		{
			std::shared_ptr<T> child{};

			const auto children = this->getChildren<T>();

			if(children.empty() == false)
			{
				child = children[x];
			}

			return child;
		}

		///
		///	Return all children of this object.
		///
		///	\param recursive If set to true, this will get all children and their children.
		///
		virtual std::vector<std::shared_ptr<Object>> getChildren(FindOption option = FindOption::Direct) const;

		///
		///	Return all children of the given type for this object.
		///
		///	\param recursive If set to true, this will get all children and their children.
		///
		template <typename T>
		auto getChildren(FindOption option = FindOption::Direct) const
		{
			std::vector<std::shared_ptr<T>> v;
			const auto children = this->getChildren(option);
			v.reserve(children.size());

			for(const auto& c : children)
			{
				const auto child = std::dynamic_pointer_cast<T>(c);

				if(child != nullptr)
				{
					v.push_back(child);
				}
			}

			return v;
		}

		///
		///	Remove this object from its parent if it has one.
		///
		///	Returns ownership of itself upon successful removal.
		///
		[[maybe_unused]] bool remove();

	protected:
		[[nodiscard]] azule::ScopedConnection addOnAddChild(std::function<void(Object*)> x);
		[[nodiscard]] azule::ScopedConnection addOnRemoveChild(std::function<void(Object*)> x);
		void track(azule::ScopedConnection x);

	private:
		virtual void onStartup();
		virtual void onShutdown();

		std::vector<std::shared_ptr<Object>> children;
		std::vector<azule::ScopedConnection> connection;
		azule::Signal<Object*> onAddChild;
		azule::Signal<Object*> onRemoveChild;
		std::string id;
		std::weak_ptr<Object> parent;
		Status status{Status::None};
	};
}

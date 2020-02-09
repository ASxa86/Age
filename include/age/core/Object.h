#pragma once

#include <age/core/export.h>
#include <age/utilities/Pimpl.h>
#include <age/core/Properties.h>

#include <functional>
#include <string>
#include <vector>

namespace sigslot
{
	class scoped_connection;
}

namespace age
{
	namespace core
	{
		///
		///	\class Object
		///
		///	\brief Base class for all objects of AGE. Designed using the composite pattern.
		///
		///	\date April 22, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Object : public Properties
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
			Object* getParent() const;

			///
			///	Return the parent as type T. Returns nullptr if the parent is not of type T.
			///
			///	\param recursive Recursively search for a parent of the given type T.
			///
			template <typename T>
			T* getParent(FindOption option = FindOption::Direct) const
			{
				const auto parent = this->getParent();
				auto parentType = dynamic_cast<T*>(parent);

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
			virtual bool addChild(std::unique_ptr<Object> x);

			template <typename T>
			[[maybe_unused]] T* addChild()
			{
				auto child = std::make_unique<T>();
				const auto p = child.get();

				if(this->addChild(std::move(child)) == true)
				{
					return p;
				}

				return nullptr;
			}

			///
			///	Return the child with the given index. Default 0.
			///
			virtual Object* getChild(size_t x = 0) const;

			///
			///	Return the child of type T with the given index. Default 0.
			///
			template <typename T>
			T* getChild(size_t x = 0) const
			{
				T* child{};

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
			virtual std::vector<Object*> getChildren(FindOption option = FindOption::Direct) const;

			///
			///	Return all children of the given type for this object.
			///
			///	\param recursive If set to true, this will get all children and their children.
			///
			template <typename T>
			std::vector<T*> getChildren(FindOption option = FindOption::Direct) const
			{
				std::vector<T*> v;
				const auto children = this->getChildren(option);
				v.reserve(children.size());

				for(const auto& c : children)
				{
					const auto child = dynamic_cast<T*>(c);

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
			[[maybe_unused]] std::unique_ptr<Object> remove();

		protected:
			[[nodiscard]] sigslot::scoped_connection addOnAddChild(std::function<void(Object*)> x);
			[[nodiscard]] sigslot::scoped_connection addOnRemoveChild(std::function<void(Object*)> x);
			void track(sigslot::scoped_connection x);

		private:
			virtual void onStartup();
			virtual void onShutdown();

			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

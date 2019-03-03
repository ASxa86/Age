#pragma once

#include <age/core/Export.h>
#include <age/core/Pimpl.h>

#include <functional>
#include <vector>

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
		class AGE_CORE_EXPORT Object : public std::enable_shared_from_this<Object>
		{
		public:
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
			virtual void initialize();

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
			T* getParent(bool recursive = false) const
			{
				const auto parent = this->getParent();
				auto parentType = dynamic_cast<T*>(parent);

				if(recursive == true)
				{
					if(parent != nullptr && parentType == nullptr)
					{
						parentType = parent->getParent<T>(recursive);
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
			T* getChild(size_t x = 0)
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
			virtual std::vector<Object*> getChildren(bool recursive = false) const;

			///
			///	Return all children of the given type for this object.
			///
			///	\param recursive If set to true, this will get all children and their children.
			///
			template <typename T>
			std::vector<T*> getChildren(bool recursive = false) const
			{
				std::vector<T*> v;
				const auto children = this->getChildren(recursive);
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

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

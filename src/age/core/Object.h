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
			virtual bool addChild(const std::shared_ptr<Object>& x);

			///
			///	Return the child with the given index. Default 0.
			///
			virtual std::shared_ptr<Object> getChild(size_t x = 0) const;

			///
			///	Return the child of type T with the given index. Default 0.
			///
			template <typename T>
			std::shared_ptr<T> getChild(size_t x = 0)
			{
				std::shared_ptr<T> child;

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
			virtual std::vector<std::shared_ptr<Object>> getChildren(bool recursive = false) const;

			///
			///	Return all children of the given type for this object.
			///
			///	\param recursive If set to true, this will get all children and their children.
			///
			template <typename T>
			std::vector<std::shared_ptr<T>> getChildren(bool recursive = false) const
			{
				std::vector<std::shared_ptr<T>> v;
				const auto children = this->getChildren(recursive);
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
			///	Remove the given object if it exists as a child.
			///
			///	Returns false if the object doesn't exist.
			///
			virtual bool removeChild(const std::shared_ptr<Object>& x);

			///
			///	Remove this object from its parent if it has one.
			///
			///	Returns false on failure to remove.
			///
			virtual bool remove();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

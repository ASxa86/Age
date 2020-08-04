#pragma once

#include <azule/core/Object.h>
#include <azule/export.hxx>

namespace azule
{
	class Component;

	///
	///	\class Entity
	///
	///	\brief This class is an id container that represents a game object.
	///
	///	This is the Entity in the Entity Component System design pattern. Use this class
	///	to define the behaviour of a game object by adding multiple components to it.
	///
	///	\date December 3, 2017
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT Entity : public azule::Object
	{
	public:
		Entity();

		bool addComponent(std::shared_ptr<azule::Component> x);

		template <typename T>
		[[maybe_unused]] T* addComponent()
		{
			static_assert(std::is_base_of<azule::Component, T>::value == true, "T must derive from azule::Component.");

			auto child = std::make_shared<T>();
			const auto p = child.get();

			if(this->addChild(child) == true)
			{
				return p;
			}

			return nullptr;
		}

	private:
		using Object::addChild;
	};
}

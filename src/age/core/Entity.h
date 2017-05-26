#pragma once

#include <age/core/Object.h>

namespace age
{
	namespace core
	{
		///
		///	\class Entity
		///
		///	\brief The Entity in Entity Component System. This class maintains a list of components that describe what this entity is.
		///
		///	\date May 25, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_CORE_EXPORT Entity : public Object
		{
		public:
			Entity();
			virtual ~Entity();

			///
			///	\brief Gets a unique ID for this entity.
			///
			uint32_t getID();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

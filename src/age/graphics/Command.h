#pragma once

#include <age/core/Object.h>
#include <age/graphics/Export.h>
#include <SFML/Window/Keyboard.hpp>

namespace age
{
	namespace core
	{
		class Entity;
	}

	namespace graphics
	{
		///
		///	\class Command
		///
		///	\brief The abstract "Command" in Command Pattern.
		///
		///	This class is an abstract class to be derived from to define a specific command
		///	to act on an entity. This is added as a child to the Entity's InputComponent.
		///
		///	\date June 9, 2017
		///
		///	\author Aaron Shelley
		///
		class AGE_GRAPHICS_EXPORT Command : public age::core::Object
		{
		public:
			Command();
			virtual ~Command() override;

			///
			///	Set the key that will be used to execute this command.
			///
			void setMappedKey(sf::Keyboard::Key x);

			///
			///	Get the key that will be used to execute this command.
			///
			sf::Keyboard::Key getMappedKey() const;

			///
			///	Override this function to define a specific command to be performed on the given entity.
			///
			virtual void execute(age::core::Entity* x) = 0;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

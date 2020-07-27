#pragma once

#include <age/core/Event.h>
#include <age/utilities/Pimpl.h>
#include <SFML/Window/Event.hpp>

namespace age
{
	namespace graphics
	{
		///
		///	\class KeyEvent
		///
		///	\brief This event manages keyboard presses and releases.
		///
		///	\date June 12, 2017
		///
		///	\author Aaron Shelley
		///
		class KeyEvent : public age::core::Event
		{
		public:
			///
			///	\enum Type
			///
			///	\brief This enumeration describes whether the key was pressed or released.
			///
			enum class Type : uint8_t
			{
				Released,
				Pressed
			};

			KeyEvent(sf::Keyboard::Key key, Type type);
			~KeyEvent() override;

			///
			///	Get the key that was pressed or released.
			///
			sf::Keyboard::Key getKey() const;

			///
			///	Get whether the key was pressed or released.
			///
			Type getType() const;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}

#pragma once

#include <azule/entity/Component.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/export.h>
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include <vector>

namespace azule
{
	///
	///	\class InputComponent
	///
	///	\brief This is an input component that manages mapped keys for a given command.
	///
	///	This class is the container for the "Command Pattern" where mapped keys are used by the
	///	PlayerInputSystem to determine which command should be ran.
	///
	///	\date June 9, 2017
	///
	///	\author Aaron Shelley
	///
	class AZULE_EXPORT InputComponent : public azule::Component
	{
	public:
		InputComponent();
		~InputComponent();

		void addKeyBinding(sf::Keyboard::Key key, const std::function<void(azule::Entity&, bool)>& x);

		const std::vector<std::pair<sf::Keyboard::Key, std::function<void(azule::Entity&, bool)>>>& getKeyBindings() const;

	private:
		std::vector<std::pair<sf::Keyboard::Key, std::function<void(azule::Entity&, bool)>>> keyBindings;
	};
}

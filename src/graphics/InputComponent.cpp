#include <azule/graphics/InputComponent.h>

using namespace azule;

InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::addKeyBinding(sf::Keyboard::Key key, const std::function<void(azule::Entity&, bool)>& x)
{
	this->keyBindings.push_back(std::make_pair(key, x));
}

const std::vector<std::pair<sf::Keyboard::Key, std::function<void(azule::Entity&, bool)>>>& InputComponent::getKeyBindings() const
{
	return this->keyBindings;
}

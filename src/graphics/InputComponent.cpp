#include <age/graphics/InputComponent.h>

using namespace age::graphics;

InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::addKeyBinding(sf::Keyboard::Key key, const std::function<void(age::entity::Entity&, bool)>& x)
{
	this->keyBindings.push_back(std::make_pair(key, x));
}

const std::vector<std::pair<sf::Keyboard::Key, std::function<void(age::entity::Entity&, bool)>>>& InputComponent::getKeyBindings() const
{
	return this->keyBindings;
}

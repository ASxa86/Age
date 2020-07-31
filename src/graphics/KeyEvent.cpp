#include <azule/graphics/KeyEvent.h>
#include <azule/utilities/PimplImpl.h>

using namespace azule;

class KeyEvent::Impl
{
public:
	Impl(sf::Keyboard::Key key, Type type) :
		key{key},
		type{type}
	{
	}

	sf::Keyboard::Key key;
	Type type;
};

KeyEvent::KeyEvent(sf::Keyboard::Key key, Type type) : azule::Event(), pimpl(key, type)
{
}

KeyEvent::~KeyEvent()
{
}

sf::Keyboard::Key KeyEvent::getKey() const
{
	return this->pimpl->key;
}

KeyEvent::Type KeyEvent::getType() const
{
	return this->pimpl->type;
}

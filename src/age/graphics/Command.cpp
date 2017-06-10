#include <age/graphics/Command.h>
#include <age/core/PimplImpl.h>

using namespace age::graphics;

class Command::Impl
{
public:
	sf::Keyboard::Key mappedKey;
};

Command::Command()
{
}

Command::~Command()
{
}

void Command::setMappedKey(sf::Keyboard::Key x)
{
	this->pimpl->mappedKey = x;
}

sf::Keyboard::Key Command::getMappedKey() const
{
	return this->pimpl->mappedKey;
}

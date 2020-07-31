#include <azule/audio/AudioEvent.h>

#include <azule/utilities/PimplImpl.h>

using namespace azule;

struct AudioEvent::Impl
{
	Impl(sf::SoundBuffer& x) : soundBuffer{x}
	{
	}

	sf::SoundBuffer& soundBuffer;
};

AudioEvent::AudioEvent(sf::SoundBuffer& x) : pimpl{x}
{
}

AudioEvent::~AudioEvent()
{
}

sf::SoundBuffer& AudioEvent::getSoundBuffer() const
{
	return this->pimpl->soundBuffer;
}

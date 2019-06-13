#include <age/audio/AudioEvent.h>

#include <age/core/PimplImpl.h>

using namespace age::audio;

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

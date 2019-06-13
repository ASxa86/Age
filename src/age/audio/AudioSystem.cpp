#include <age/audio/AudioSystem.h>

#include <age/audio/AudioEvent.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <SFML/Audio/Sound.hpp>

using namespace age::audio;

struct AudioSystem::Impl
{
	sf::Sound sound;
};

AudioSystem::AudioSystem()
{
}

AudioSystem::~AudioSystem()
{
}

void AudioSystem::initialize()
{
	age::core::EventQueue::Instance().addEventHandler([this](auto x) { this->onEvent(x); }, this);
}

void AudioSystem::onEvent(age::core::Event* x)
{
	auto event = dynamic_cast<AudioEvent*>(x);

	if(event != nullptr)
	{
		this->pimpl->sound.setBuffer(event->getSoundBuffer());
		this->pimpl->sound.play();
	}
}

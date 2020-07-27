#include <azule/audio/AudioSystem.h>

#include <azule/audio/AudioEvent.h>
#include <azule/core/EventQueue.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/utilities/Signal.h>
#include <SFML/Audio/Sound.hpp>

using namespace azule::audio;

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

void AudioSystem::onStartup()
{
	this->track(azule::core::EventQueue::Instance().addEventHandler([this](auto x) { this->onEvent(x); }));
}

void AudioSystem::onEvent(azule::core::Event* x)
{
	auto event = dynamic_cast<AudioEvent*>(x);

	if(event != nullptr)
	{
		this->pimpl->sound.setBuffer(event->getSoundBuffer());
		this->pimpl->sound.play();
	}
}

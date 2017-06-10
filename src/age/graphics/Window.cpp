#include <age/core/Entity.h>
#include <age/core/Engine.h>
#include <age/core/EngineState.h>
#include <age/core/PimplImpl.h>
#include <age/core/Timer.h>
#include <age/graphics/DrawableComponent.h>
#include <age/graphics/Window.h>

#include <SFML/Graphics.hpp>

using namespace age::core;
using namespace age::graphics;

class Window::Impl
{
public:
	Impl(uint16_t width, uint16_t height) : window{sf::VideoMode{width, height}, "AGE"}
	{
		this->window.setVerticalSyncEnabled(false);
		this->window.setFramerateLimit(0);
	}

	sf::RenderWindow window;
	Timer timer;
};

Window::Window(uint16_t width, uint16_t height) : RenderSystem(), pimpl(width, height)
{
}

Window::~Window()
{
}

void Window::pollEvents()
{
	sf::Event e;
	const auto engine = this->getParent<Engine>();

	// This entire event loop needs to occur elsewhere so that event can be handled before this frame().
	while(this->pimpl->window.pollEvent(e) == true)
	{
		switch(e.type)
		{
			case sf::Event::EventType::Closed:
				this->pimpl->window.close();
				engine->setEngineState(EngineState::State::Exit);
				break;
			case sf::Event::EventType::KeyPressed:
				// engine->sendEvent(std::make_unique<KeyEvent>());
				break;
			case sf::Event::EventType::KeyReleased:
				// engine->sendEvent(std::make_unique<KeyEvent>());
				break;
			case sf::Event::EventType::Resized:
				// engine->sendEvent(std::make_unique<ResizeEvent>());
				break;
			default:
				break;
		}
	}
}

void Window::frame(std::chrono::microseconds /*x*/)
{
	if(this->pimpl->window.isOpen() == true)
	{
		auto delta = std::chrono::duration_cast<age::core::seconds>(this->pimpl->timer.reset());
		this->pimpl->window.clear();

		const auto entities = this->getEntities();

		for(const auto& entity : entities)
		{
			const auto drawables = entity->getChildren<DrawableComponent>();

			for(const auto& drawable : drawables)
			{
				drawable->draw(this->pimpl->window);
			}
		}

		this->pimpl->window.display();
	}
}

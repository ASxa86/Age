#include <azule/graphics/Window.h>

#include <azule/core/Configuration.h>
#include <azule/core/Engine.h>
#include <azule/core/EngineState.h>
#include <azule/core/EventQueue.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/core/Timer.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/TransformComponent.h>
#include <azule/graphics/KeyEvent.h>
#include <azule/graphics/RenderSystem.h>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <numeric>
#include <sstream>

using namespace azule::core;
using namespace azule::entity;
using namespace azule::graphics;
using namespace azule::math;

class Window::Impl
{
public:
	Impl(unsigned int width, unsigned int height)
		: settings{0, 0, 8}, window{sf::VideoMode{width, height}, "Azule", sf::Style::Close | sf::Style::Resize, settings}
	{
		this->window.setVerticalSyncEnabled(false);
		this->window.setFramerateLimit(0);

		this->font.loadFromFile((Configuration::Instance().getPathData() / "fonts/sansation.ttf").string());
		this->text.setFont(this->font);
		this->text.setPosition({10.0, 30.0});
	}

	sf::ContextSettings settings;
	sf::RenderWindow window;
	Timer timer;

	// Temporary until I find a generic way to handle GUI widgets.
	sf::Text text;
	sf::Font font;
};

Window::Window(unsigned int width, unsigned int height) : Processor(), pimpl(width, height)
{
	this->addVariableFunction([this](auto x) { this->variable(x); });
	this->addRenderFunction([this](auto x) { this->render(x); });
}

Window::~Window()
{
}

unsigned int Window::getWidth() const
{
	return this->pimpl->window.getSize().x;
}

unsigned int Window::getHeight() const
{
	return this->pimpl->window.getSize().y;
}

void Window::variable(std::chrono::microseconds)
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
				engine->setEngineState(EngineState::State::Shutdown);
				break;
			case sf::Event::EventType::KeyPressed:
				EventQueue::Instance().sendEvent(std::make_unique<KeyEvent>(e.key.code, KeyEvent::Type::Pressed));
				break;
			case sf::Event::EventType::KeyReleased:
				EventQueue::Instance().sendEvent(std::make_unique<KeyEvent>(e.key.code, KeyEvent::Type::Released));
				break;
			case sf::Event::EventType::Resized:
				// engine->sendEvent(std::make_unique<ResizeEvent>());
				break;
			default:
				break;
		}
	}
}

void Window::render(std::chrono::microseconds x)
{
	if(this->pimpl->window.isOpen() == true)
	{
		this->pimpl->window.clear();

		const auto renderSystems = this->getChildren<RenderSystem>();

		for(const auto& system : renderSystems)
		{
			system->render(this->pimpl->window, x);
		}

		// FPS
		static double elapsed = 0.0;
		const auto delta = std::chrono::duration_cast<azule::core::seconds>(this->pimpl->timer.reset());
		elapsed += delta.count();

		if(elapsed >= 0.5)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(1) << 1.0 / delta.count();
			this->pimpl->text.setString("FPS: " + ss.str());
			elapsed = 0.0;
		}

		this->pimpl->window.draw(this->pimpl->text);
		this->pimpl->window.display();
	}
}

#include <Application.h>
#include <age/core/Engine.h>
#include <age/core/PimplImpl.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>

using namespace age;
using namespace age::entity;

struct Application::Impl
{
	age::core::Engine engine;
};

Application::Application(int argc, char** argv) : QApplication(argc, argv), pimpl()
{
	auto manager = this->pimpl->engine.addChild<EntityDatabase>();
	manager->addEntity();
}

Application::~Application()
{
}

Application* Application::Instance()
{
	return static_cast<Application*>(QCoreApplication::instance());
}

age::core::Engine& Application::getEngine()
{
	return this->pimpl->engine;
}

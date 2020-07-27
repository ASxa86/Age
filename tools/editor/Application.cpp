#include <Application.h>
#include <azule/core/Engine.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>

using namespace azule;
using namespace azule::entity;

struct Application::Impl
{
	azule::core::Engine engine;
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

azule::core::Engine& Application::getEngine()
{
	return this->pimpl->engine;
}

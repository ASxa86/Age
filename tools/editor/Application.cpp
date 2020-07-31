#include <Application.h>
#include <azule/core/Engine.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>

using namespace azule;
using namespace azule;

struct Application::Impl
{
	azule::Engine engine;
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

azule::Engine& Application::getEngine()
{
	return this->pimpl->engine;
}

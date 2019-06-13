#include <editor/Application.h>

#include <age/core/Engine.h>
#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>

using namespace age;
using namespace age::entity;

struct Application::Impl
{
	age::core::Engine engine;
};

Application::Application(int argc, char** argv) : QApplication(argc, argv), pimpl()
{
	auto manager = this->pimpl->engine.addChild<EntityManager>();
	manager->create();
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

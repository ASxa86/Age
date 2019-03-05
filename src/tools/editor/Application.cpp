#include <tools/editor/Application.h>

#include <age/core/Engine.h>
#include <age/core/PimplImpl.h>

using namespace age;

struct Application::Impl
{
	age::core::Engine engine;
};

Application::Application(int argc, char** argv) : QApplication(argc, argv), pimpl()
{
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

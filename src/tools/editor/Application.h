#pragma once

#include <age/core/Pimpl.h>
#include <QtWidgets/QApplication>

namespace age
{
	namespace core
	{
		class Engine;
	}

	class Application final : public QApplication
	{
	public:
		Application(int argc, char** argv);
		~Application();

		static Application* Instance();

		age::core::Engine& getEngine();

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

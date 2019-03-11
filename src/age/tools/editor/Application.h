#pragma once

#include <age/core/Pimpl.h>
#include <QtWidgets/QApplication>

namespace age
{
	namespace core
	{
		class Engine;
	}

	///
	///	\class Application
	///
	///	\brief QApplication overload for managing age library components across widgets.
	///
	///	\author Aaron Shelley
	///
	///	\date March 9, 2019
	///
	class Application final : public QApplication
	{
	public:
		Application(int argc, char** argv);
		~Application();

		///
		///	Return the instance of QApplication casted to Application.
		///
		static Application* Instance();

		///
		///	Get the core game engine for the application.
		///
		age::core::Engine& getEngine();

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

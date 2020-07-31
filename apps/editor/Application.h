#pragma once

#include <azule/entity/Component.h>
#include <azule/utilities/Pimpl.h>
#include <QtWidgets/QApplication>

namespace azule
{
	class Engine;

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
		Q_OBJECT

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
		azule::Engine& getEngine();

	signals:
		void componentSelected(azule::Component*);

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

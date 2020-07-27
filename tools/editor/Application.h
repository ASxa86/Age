#pragma once

#include <age/utilities/Pimpl.h>
#include <age/entity/Component.h>
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
		age::core::Engine& getEngine();

	signals:
		void componentSelected(age::entity::Component*);

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

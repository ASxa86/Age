#pragma once

#include <azule/utilities/Pimpl.h>
#include <QtWidgets/QMainWindow>

namespace azule
{
	///
	///	\class MainWindow
	///
	///	\brief The QMainWindow overload of the application.
	///
	///	\author Aaron Shelley
	///
	///	\date March 9, 2019
	///
	class MainWindow final : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = nullptr);
		~MainWindow();

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

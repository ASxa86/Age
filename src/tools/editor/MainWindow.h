#pragma once

#include <age/core/Pimpl.h>
#include <QtWidgets/QMainWindow>

namespace age
{
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

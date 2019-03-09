#pragma once

#include <age/core/Pimpl.h>
#include <QtWidgets/QDockWidget>

namespace age
{
	class DockWidgetEntity final : public QDockWidget
	{
	public:
		DockWidgetEntity(QWidget* parent = nullptr);
		~DockWidgetEntity();

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

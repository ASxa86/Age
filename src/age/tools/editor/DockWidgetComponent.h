#pragma once

#include <QtWidgets/QDockWidget>

namespace age
{
	class DockWidgetComponent : public QDockWidget
	{
		Q_OBJECT

	public:
		DockWidgetComponent(QWidget* parent = nullptr);

	private:
	};
}

#pragma once

#include <QtWidgets/QDockWidget>

namespace azule
{
	class DockWidgetComponent : public QDockWidget
	{
		Q_OBJECT

	public:
		DockWidgetComponent(QWidget* parent = nullptr);

	private:
	};
}

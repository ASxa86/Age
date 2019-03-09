#pragma once

#include <QtWidgets/QListWidget>

namespace age
{
	///
	///	\class ListWidgetComponents
	///
	///	\brief List the components available within the ComponentFactory.
	///
	///	\date March 5, 2019
	///
	///	\author Aaron Shelley
	///
	class ListWidgetComponents final : public QListWidget
	{
		Q_OBJECT

	public:
		ListWidgetComponents(QWidget* parent = nullptr);
		~ListWidgetComponents();
	};
}

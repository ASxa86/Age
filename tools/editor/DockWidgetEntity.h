#pragma once

#include <azule/utilities/Pimpl.h>
#include <QtWidgets/QDockWidget>

namespace azule
{
	///
	///	\class DockWidgetEntity
	///
	///	\brief A dockable window used to list and edit entities and their components.
	///
	///	\author Aaron Shelley
	///
	///	\date March 9, 2019
	///
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

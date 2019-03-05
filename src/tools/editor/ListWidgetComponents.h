#pragma once

#include <QtWidgets/QListWidget>

#include <age/core/Pimpl.h>

namespace age
{
	namespace entity
	{
		class Entity;
	}

	class ListWidgetComponents final : public QListWidget
	{
		Q_OBJECT

	public:
		ListWidgetComponents(QWidget* parent = nullptr);
		~ListWidgetComponents();

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

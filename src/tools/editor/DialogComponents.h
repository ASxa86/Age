#pragma once

#include <age/entity/Entity.h>
#include <QtWidgets/QDialog>

namespace age
{
	class DialogComponents : public QDialog
	{
		Q_OBJECT

	public:
		DialogComponents(age::entity::Entity e, QWidget* parent = nullptr);
		~DialogComponents();

	private:
		age::entity::Entity entity;
	};
}

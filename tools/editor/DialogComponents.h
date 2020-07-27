#pragma once

#include <age/entity/Entity.h>
#include <QtWidgets/QDialog>

namespace age
{
	///
	///	\class DialogComponents
	///
	///	\brief A dialog for choosing a new component to add to an Entity.
	///
	///	\author Aaron Shelley
	///
	///	\date March 9, 2019
	///
	class DialogComponents : public QDialog
	{
		Q_OBJECT

	public:
		///
		///	\param e The entity to add a new component too.
		///
		DialogComponents(age::entity::Entity* e, QWidget* parent = nullptr);
		~DialogComponents();

	private:
		age::entity::Entity* entity;
	};
}

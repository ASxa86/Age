#pragma once

#include <azule/utilities/Pimpl.h>
#include <QtWidgets/QTreeWidget>
#include <typeindex>

namespace azule
{
	class Component;
	class Entity;

	///
	///	\class TreeWidgetEntity
	///
	///	\brief A QTreeWidget used to list and select entities and components that exist within azule::EntityDatabase.
	///
	///	\author Aaron Shelley
	///
	///	\date March 9, 2019
	///
	class TreeWidgetEntity final : public QTreeWidget
	{
		Q_OBJECT

	public:
		///
		///	\enum ItemType
		///
		///	\brief This enumeration describes the different types of tree items that exist within the tree.
		///
		enum ItemType : int
		{
			Entity = QTreeWidgetItem::UserType + 1,
			Component
		};

		TreeWidgetEntity(QWidget* parent = nullptr);
		~TreeWidgetEntity();

		///
		///	Add a tree node to list and edit the given entity.
		///
		void addEntity(azule::Entity* x);

		///
		///	Remove the associated tree tode for the given entity.
		///
		void removeEntity(azule::Entity* x);

		///
		///	Add a tree node to the list under the node associated with the given entity.
		///
		void addComponent(azule::Entity* x, azule::Component* c);

		///
		///	Add a tree node to the list under the given tree node.
		///
		void addComponent(QTreeWidgetItem* item, azule::Component* c);

		///
		///	Remove the associated tree node for the given component type of the given entity.
		///
		void removeComponent(azule::Entity* x, azule::Component* c);

		///
		///	Get the tree node associated with the given entity.
		///
		QTreeWidgetItem* findItem(azule::Entity* x);

		///
		///	Get the tree node associated with the given component type of the given entity.
		///
		QTreeWidgetItem* findItem(azule::Entity* x, azule::Component* c);

		///
		///	Overload the default size hint to adjust the default size within an application.
		///
		virtual QSize sizeHint() const override;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}

#pragma once

#include <age/core/Pimpl.h>
#include <QtWidgets/QTreeWidget>
#include <typeindex>

namespace age
{
	namespace entity
	{
		class Component;
		class Entity;
	}

	///
	///	\class TreeWidgetEntity
	///
	///	\brief A QTreeWidget used to list and select entities and components that exist within age::entity::EntityDatabase.
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
		void addEntity(const age::entity::Entity& x);

		///
		///	Remove the associated tree tode for the given entity.
		///
		void removeEntity(const age::entity::Entity& x);

		///
		///	Add a tree node to the list under the node associated with the given entity.
		///
		void addComponent(const age::entity::Entity& x, age::entity::Component* c);

		///
		///	Add a tree node to the list under the given tree node.
		///
		void addComponent(QTreeWidgetItem* item, age::entity::Component* c);

		///
		///	Remove the associated tree node for the given component type of the given entity.
		///
		void removeComponent(const age::entity::Entity& x, age::entity::Component* c);

		///
		///	Get the tree node associated with the given entity.
		///
		QTreeWidgetItem* findItem(const age::entity::Entity& x);

		///
		///	Get the tree node associated with the given component type of the given entity.
		///
		QTreeWidgetItem* findItem(const age::entity::Entity& x, age::entity::Component* c);

		///
		///	Overload the default size hint to adjust the default size within an application.
		///
		virtual QSize sizeHint() const override;
	};
}

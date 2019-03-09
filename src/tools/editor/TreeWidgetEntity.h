#pragma once

#include <age/core/Pimpl.h>
#include <QtWidgets/QTreeWidget>
#include <typeindex>

namespace age
{
	namespace entity
	{
		class Entity;
	}

	class TreeWidgetEntity final : public QTreeWidget
	{
		Q_OBJECT

	public:
		TreeWidgetEntity(QWidget* parent = nullptr);
		~TreeWidgetEntity();

		void addEntity(const age::entity::Entity& x);
		void removeEntity(const age::entity::Entity& x);
		void addComponent(const age::entity::Entity& x, const std::type_index& t);
		void addComponent(QTreeWidgetItem* item, const std::type_index& t);
		void removeComponent(const age::entity::Entity& x, const std::type_index& t);
		QTreeWidgetItem* findItem(const age::entity::Entity& x);
		QTreeWidgetItem* findItem(const age::entity::Entity& x, const std::type_index& t);
		virtual QSize sizeHint() const override;
	};
}

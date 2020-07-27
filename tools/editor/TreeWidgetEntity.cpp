#include <TreeWidgetEntity.h>

#include <Application.h>
#include <GUIComponent.h>
#include <azule/core/Engine.h>
#include <azule/core/EventQueue.h>
#include <azule/core/Reflection.h>
#include <azule/entity/Component.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/EntityEvent.h>
#include <azule/utilities/PimplImpl.h>
#include <azule/utilities/Signal.h>
#include <QtCore/QSize>

using namespace azule;
using namespace azule::core;
using namespace azule::entity;
using namespace azule::utilities;

Q_DECLARE_METATYPE(azule::entity::Entity*)
Q_DECLARE_METATYPE(azule::entity::Component*)

struct TreeWidgetEntity::Impl
{
	ScopedConnection connection;
};

TreeWidgetEntity::TreeWidgetEntity(QWidget* parent) : QTreeWidget(parent)
{
	Reflection::Instance().add<azule::GUIComponent>("GUIComponent");
	qRegisterMetaType<azule::entity::Entity*>();
	qRegisterMetaType<azule::entity::Component*>();

	this->pimpl->connection = EventQueue::Instance().addEventHandler([this](Event* x) {
		auto evt = dynamic_cast<EntityEvent*>(x);

		if(evt != nullptr)
		{
			switch(evt->getType())
			{
				case EntityEvent::Type::EntityAdded:
					this->addEntity(evt->getEntity());
					break;

				case EntityEvent::Type::EntityRemoved:
					this->removeEntity(evt->getEntity());
					break;

				case EntityEvent::Type::ComponentAdded:
					this->addComponent(evt->getEntity(), evt->Component);
					break;

				case EntityEvent::Type::ComponentRemoved:
					this->removeComponent(evt->getEntity(), evt->Component);
					break;

				default:
					break;
			}
		}
	});

	this->connect(this, &QTreeWidget::itemChanged, this, [this](QTreeWidgetItem* item) {
		if(item->type() == ItemType::Entity)
		{
			auto entity = item->data(0, Qt::UserRole).value<azule::entity::Entity*>();

			if(entity != nullptr)
			{
				auto gui = entity->addComponent<GUIComponent>();
				gui->ID = item->text(0).toStdString();
			}
		}
	});

	this->connect(this, &QTreeWidget::itemClicked, this, [this](QTreeWidgetItem* item) {
		if(item->type() == ItemType::Component)
		{
			auto component = item->data(0, Qt::UserRole).value<azule::entity::Component*>();
			Application::Instance()->componentSelected(component);
		}
	});

	const auto manager = Application::Instance()->getEngine().getChild<EntityDatabase>();

	if(manager != nullptr)
	{
		const auto& entities = manager->getChildren<azule::entity::Entity>();

		for(const auto& entity : entities)
		{
			this->addEntity(entity);
		}
	}
}

TreeWidgetEntity::~TreeWidgetEntity()
{
}

void TreeWidgetEntity::addEntity(azule::entity::Entity* x)
{
	// Block the item changed signal until after we've fully added the entity node along with
	// its component nodes.
	QSignalBlocker block(this);
	auto item = new QTreeWidgetItem(this, ItemType::Entity);
	item->setText(0, "Entity");
	item->setData(0, Qt::UserRole, QVariant::fromValue(x));
	item->setIcon(0, QIcon(":icons/pawn.png"));
	item->setFlags(item->flags() | Qt::ItemFlag::ItemIsEditable);

	auto components = x->getChildren<azule::entity::Component>();

	for(const auto& component : components)
	{
		this->addComponent(item, component);
	}
}

void TreeWidgetEntity::removeEntity(azule::entity::Entity* x)
{
	delete this->findItem(x);
}

void TreeWidgetEntity::addComponent(azule::entity::Entity* e, azule::entity::Component* c)
{
	auto item = this->findItem(e);

	if(item != nullptr)
	{
		this->addComponent(item, c);
	}
}

void TreeWidgetEntity::addComponent(QTreeWidgetItem* item, azule::entity::Component* c)
{
	const auto componentItem = new QTreeWidgetItem(item, ItemType::Component);
	auto type = Reflection::Instance().get(typeid(*c));
	componentItem->setText(0, QString::fromStdString(type->Name));
	componentItem->setData(0, Qt::UserRole, QVariant::fromValue(c));
	item->setExpanded(true);
}

void TreeWidgetEntity::removeComponent(azule::entity::Entity* e, azule::entity::Component* c)
{
	delete this->findItem(e, c);
}

QTreeWidgetItem* TreeWidgetEntity::findItem(azule::entity::Entity* x)
{
	for(auto i = 0; i < this->topLevelItemCount(); i++)
	{
		auto item = this->topLevelItem(i);

		if(item->data(0, Qt::UserRole).value<azule::entity::Entity*>() == x)
		{
			return item;
		}
	}

	return nullptr;
}

QTreeWidgetItem* TreeWidgetEntity::findItem(azule::entity::Entity* e, azule::entity::Component* c)
{
	auto item = this->findItem(e);

	if(item != nullptr)
	{
		for(auto i = 0; i < item->childCount(); i++)
		{
			auto child = item->child(i);

			auto type = Reflection::Instance().get(typeid(*c));

			if(child->text(0) == QString::fromStdString(type->Name))
			{
				return child;
			}
		}
	}

	return nullptr;
}

QSize TreeWidgetEntity::sizeHint() const
{
	const auto hint = QTreeWidget::sizeHint();
	return {450, hint.width()};
}

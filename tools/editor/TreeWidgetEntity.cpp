#include <TreeWidgetEntity.h>

#include <Application.h>
#include <GUIComponent.h>
#include <age/core/Engine.h>
#include <age/core/EventQueue.h>
#include <age/core/Factory.h>
#include <age/core/PimplImpl.h>
#include <age/core/SigSlot.h>
#include <age/entity/Component.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/EntityEvent.h>
#include <QtCore/QSize>

using namespace age;
using namespace age::core;
using namespace age::entity;

Q_DECLARE_METATYPE(age::entity::Entity*)
Q_DECLARE_METATYPE(age::entity::Component*)

struct TreeWidgetEntity::Impl
{
	sigslot::scoped_connection connection;
};

TreeWidgetEntity::TreeWidgetEntity(QWidget* parent) : QTreeWidget(parent)
{
	AgeFactoryRegister(age::GUIComponent);
	qRegisterMetaType<age::entity::Entity*>();
	qRegisterMetaType<age::entity::Component*>();

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
			auto entity = item->data(0, Qt::UserRole).value<age::entity::Entity*>();

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
			auto component = item->data(0, Qt::UserRole).value<age::entity::Component*>();
			Application::Instance()->componentSelected(component);
		}
	});

	const auto manager = Application::Instance()->getEngine().getChild<EntityDatabase>();

	if(manager != nullptr)
	{
		const auto& entities = manager->getChildren<age::entity::Entity>();

		for(const auto& entity : entities)
		{
			this->addEntity(entity);
		}
	}
}

TreeWidgetEntity::~TreeWidgetEntity()
{
}

void TreeWidgetEntity::addEntity(age::entity::Entity* x)
{
	// Block the item changed signal until after we've fully added the entity node along with
	// its component nodes.
	QSignalBlocker block(this);
	auto item = new QTreeWidgetItem(this, ItemType::Entity);
	item->setText(0, "Entity");
	item->setData(0, Qt::UserRole, QVariant::fromValue(x));
	item->setIcon(0, QIcon(":icons/pawn.png"));
	item->setFlags(item->flags() | Qt::ItemFlag::ItemIsEditable);

	auto components = x->getChildren<age::entity::Component>();

	for(const auto& component : components)
	{
		this->addComponent(item, component);
	}
}

void TreeWidgetEntity::removeEntity(age::entity::Entity* x)
{
	delete this->findItem(x);
}

void TreeWidgetEntity::addComponent(age::entity::Entity* e, age::entity::Component* c)
{
	auto item = this->findItem(e);

	if(item != nullptr)
	{
		this->addComponent(item, c);
	}
}

void TreeWidgetEntity::addComponent(QTreeWidgetItem* item, age::entity::Component* c)
{
	const auto componentItem = new QTreeWidgetItem(item, ItemType::Component);
	auto type = Factory::Instance().getType(typeid(*c));
	componentItem->setText(0, QString::fromStdString(type.NameClean));
	componentItem->setData(0, Qt::UserRole, QVariant::fromValue(c));
	item->setExpanded(true);
}

void TreeWidgetEntity::removeComponent(age::entity::Entity* e, age::entity::Component* c)
{
	delete this->findItem(e, c);
}

QTreeWidgetItem* TreeWidgetEntity::findItem(age::entity::Entity* x)
{
	for(auto i = 0; i < this->topLevelItemCount(); i++)
	{
		auto item = this->topLevelItem(i);

		if(item->data(0, Qt::UserRole).value<age::entity::Entity*>() == x)
		{
			return item;
		}
	}

	return nullptr;
}

QTreeWidgetItem* TreeWidgetEntity::findItem(age::entity::Entity* e, age::entity::Component* c)
{
	auto item = this->findItem(e);

	if(item != nullptr)
	{
		for(auto i = 0; i < item->childCount(); i++)
		{
			auto child = item->child(i);

			auto type = Factory::Instance().getType(typeid(*c));

			if(child->text(0) == QString::fromStdString(type.NameClean))
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

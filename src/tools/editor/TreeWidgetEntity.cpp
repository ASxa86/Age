#include <tools/editor/TreeWidgetEntity.h>

#include <age/core/Engine.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/EntityManager.h>
#include <tools/editor/Application.h>
#include <tools/editor/Properties.h>
#include <QtCore/QSize>

using namespace age;
using namespace age::core;
using namespace age::entity;

TreeWidgetEntity::TreeWidgetEntity(QWidget* parent) : QTreeWidget(parent)
{
	EventQueue::Instance().addEventHandler([this](Event* x) {
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
					this->addComponent(evt->getEntity(), evt->getComponentType());
					break;
				case EntityEvent::Type::ComponentRemoved:
					this->removeComponent(evt->getEntity(), evt->getComponentType());
					break;
				default:
					break;
			}
		}
	});

	auto manager = Application::Instance()->getEngine().getChild<EntityManager>();

	if(manager != nullptr)
	{
		const auto& entities = manager->getEntities();

		for(const auto& entity : entities)
		{
			this->addEntity(entity);
		}
	}
}

TreeWidgetEntity::~TreeWidgetEntity()
{
}

void TreeWidgetEntity::addEntity(const age::entity::Entity& x)
{
	auto item = new QTreeWidgetItem(this);
	item->setText(0, "Entity");
	item->setData(0, Qt::UserRole, x.getID());

	auto componentTypes = x.getComponentTypes();

	for(const auto& type : componentTypes)
	{
		this->addComponent(item, type);
	}
}

void TreeWidgetEntity::removeEntity(const age::entity::Entity& x)
{
	delete this->findItem(x);
}

void TreeWidgetEntity::addComponent(const age::entity::Entity& e, const std::type_index& t)
{
	auto item = this->findItem(e);

	if(item != nullptr)
	{
		this->addComponent(item, t);
	}
}

void TreeWidgetEntity::addComponent(QTreeWidgetItem* item, const std::type_index& t)
{
	auto componentItem = new QTreeWidgetItem(item);
	auto name = Property::Alias[t];
	componentItem->setText(0, QString::fromStdString(name));
	item->setExpanded(true);
}

void TreeWidgetEntity::removeComponent(const age::entity::Entity& e, const std::type_index& t)
{
	delete this->findItem(e, t);
}

QTreeWidgetItem* TreeWidgetEntity::findItem(const age::entity::Entity& x)
{
	for(auto i = 0; i < this->topLevelItemCount(); i++)
	{
		auto item = this->topLevelItem(i);

		if(item->data(0, Qt::UserRole).toInt() == x.getID())
		{
			return item;
		}
	}

	return nullptr;
}

QTreeWidgetItem* TreeWidgetEntity::findItem(const age::entity::Entity& e, const std::type_index& t)
{
	auto item = this->findItem(e);

	if(item != nullptr)
	{
		for(auto i = 0; i < item->childCount(); i++)
		{
			auto child = item->child(i);

			if(child->text(0) == QString::fromStdString(Property::Alias[t]))
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

#include <age/tools/editor/TreeWidgetEntity.h>

#include <age/core/Engine.h>
#include <age/core/EventQueue.h>
#include <age/core/PimplImpl.h>
#include <age/entity/Component.h>
#include <age/entity/ComponentFactory.h>
#include <age/entity/EntityEvent.h>
#include <age/entity/EntityManager.h>
#include <age/tools/editor/Application.h>
#include <age/tools/editor/GUIComponent.h>
#include <age/tools/editor/Properties.h>
#include <QtCore/QSize>

using namespace age;
using namespace age::core;
using namespace age::entity;

Q_DECLARE_METATYPE(age::entity::Entity)

TreeWidgetEntity::TreeWidgetEntity(QWidget* parent) : QTreeWidget(parent)
{
	qRegisterMetaType<age::entity::Entity>();

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

	this->connect(this, &QTreeWidget::itemChanged, this, [this](QTreeWidgetItem* item) {
		if(item->type() == ItemType::Entity)
		{
			auto entity = item->data(0, Qt::UserRole).value<age::entity::Entity>();

			if(entity.valid() == true)
			{
				auto& gui = entity.addComponent<GUIComponent>();
				gui.ID = item->text(0).toStdString();
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
	// Block the item changed signal until after we've fully added the entity node along with
	// its component nodes.
	QSignalBlocker block(this);
	auto item = new QTreeWidgetItem(this, ItemType::Entity);
	item->setText(0, "Entity");
	item->setData(0, Qt::UserRole, QVariant::fromValue(x));
	item->setIcon(0, QIcon(":icons/pawn.png"));
	item->setFlags(item->flags() | Qt::ItemFlag::ItemIsEditable);

	auto components = x.getComponents();

	for(const auto& component : components)
	{
		this->addComponent(item, typeid(*component));
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
	const auto componentItem = new QTreeWidgetItem(item, ItemType::Component);
	const auto name = ComponentFactory::Instance().alias(t);
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

		if(item->data(0, Qt::UserRole).value<age::entity::Entity>() == x)
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

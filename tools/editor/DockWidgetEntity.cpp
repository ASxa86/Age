#include <Application.h>
#include <DialogComponents.h>
#include <DockWidgetEntity.h>
#include <TreeWidgetEntity.h>
#include <azule/core/Engine.h>
#include <azule/entity/Component.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/utilities/PimplImpl.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>

#include <iostream>

using namespace azule;
using namespace azule;

Q_DECLARE_METATYPE(azule::Entity*)
Q_DECLARE_METATYPE(azule::Component*)

struct DockWidgetEntity::Impl
{
	QMenu* contextMenu{nullptr};
};

DockWidgetEntity::DockWidgetEntity(QWidget* parent) : QDockWidget(parent)
{
	qRegisterMetaType<azule::Entity*>();
	qRegisterMetaType<azule::Component*>();

	const auto widget = new QWidget();
	const auto vLayout = new QVBoxLayout(widget);
	vLayout->setMargin(0);
	vLayout->setSpacing(0);

	const auto tbEntity = new QToolBar();
	tbEntity->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);

	const auto twEntity = new TreeWidgetEntity();
	twEntity->setHeaderHidden(true);
	twEntity->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
	twEntity->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	twEntity->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	vLayout->addWidget(tbEntity);
	vLayout->addWidget(twEntity);
	this->setWidget(widget);

	const auto addEntity = [this, twEntity] {
		const auto manager = Application::Instance()->getEngine().getChild<EntityDatabase>();

		if(manager != nullptr)
		{
			manager->addEntity();
		}
	};

	this->connect(tbEntity->addAction(QIcon(":icons/plus.png"), "Add Entity"), &QAction::triggered, this, addEntity);

	this->pimpl->contextMenu = new QMenu(this);
	this->connect(this->pimpl->contextMenu->addAction("Add Node"), &QAction::triggered, this, addEntity);
	this->connect(this->pimpl->contextMenu->addAction("Delete Node(s)"), &QAction::triggered, this, [this, twEntity] {
		const auto items = twEntity->selectedItems();

		for(auto item : items)
		{
			switch(item->type())
			{
				case TreeWidgetEntity::ItemType::Entity:
				{
					auto entity = item->data(0, Qt::UserRole).value<azule::Entity*>();
					entity->remove();
				}
				break;

				case TreeWidgetEntity::ItemType::Component:
				{
					auto component = item->data(0, Qt::UserRole).value<azule::Component*>();
					component->remove();
				}
				break;
			}
		}
	});

	this->pimpl->contextMenu->addSeparator();
	auto actComponent = this->pimpl->contextMenu->addAction("Add Component");
	this->connect(actComponent, &QAction::triggered, this, [this, twEntity] {
		const auto items = twEntity->selectedItems();

		if(items.empty() == false)
		{
			const auto& item = items[0];
			const auto entity = item->data(0, Qt::UserRole).value<azule::Entity*>();
			const auto dlgComponents = new DialogComponents(entity);
			dlgComponents->setModal(true);
			dlgComponents->setAttribute(Qt::WA_DeleteOnClose);
			dlgComponents->resize(500, 500);
			dlgComponents->show();
		}
	});

	this->connect(twEntity, &TreeWidgetEntity::customContextMenuRequested, this, [this, twEntity, actComponent](const QPoint& pos) {
		actComponent->setEnabled(false);

		const auto items = twEntity->selectedItems();

		if(items.size() == 1)
		{
			const auto& item = items[0];

			if(item != nullptr && item->type() == TreeWidgetEntity::ItemType::Entity)
			{
				actComponent->setEnabled(true);
			}
		}

		this->pimpl->contextMenu->popup(twEntity->mapToGlobal(pos));
	});
}

DockWidgetEntity::~DockWidgetEntity()
{
}

#include <tools/editor/DockWidgetEntity.h>

#include <age/core/Engine.h>
#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>
#include <tools/editor/Application.h>
#include <tools/editor/DialogComponents.h>
#include <tools/editor/TreeWidgetEntity.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>

using namespace age;
using namespace age::entity;

struct DockWidgetEntity::Impl
{
	QMenu* contextMenu{nullptr};
};

DockWidgetEntity::DockWidgetEntity(QWidget* parent) : QDockWidget(parent)
{
	const auto widget = new QWidget();
	const auto vLayout = new QVBoxLayout(widget);

	const auto tbEntity = new QToolBar();

	const auto twEntity = new TreeWidgetEntity();
	twEntity->setHeaderHidden(true);
	twEntity->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	vLayout->setMargin(0);
	vLayout->addWidget(tbEntity);
	vLayout->addWidget(twEntity);
	this->setWidget(widget);

	const auto addEntity = [this, twEntity] {
		const auto manager = Application::Instance()->getEngine().addChild<EntityManager>();

		if(manager != nullptr)
		{
			manager->create();
		}
	};

	this->connect(tbEntity->addAction("+"), &QAction::triggered, this, addEntity);

	this->pimpl->contextMenu = new QMenu(this);
	this->connect(this->pimpl->contextMenu->addAction("Add Node"), &QAction::triggered, this, addEntity);

	this->connect(twEntity, &TreeWidgetEntity::customContextMenuRequested, this,
				  [this, twEntity](const QPoint& pos) { this->pimpl->contextMenu->popup(twEntity->mapToGlobal(pos)); });
}

DockWidgetEntity::~DockWidgetEntity()
{
}

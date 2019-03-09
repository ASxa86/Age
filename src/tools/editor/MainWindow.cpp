#include <tools/editor/MainWindow.h>

#include <age/core/Engine.h>
#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>
#include <tools/editor/Application.h>
#include <tools/editor/DialogComponents.h>
#include <tools/editor/DockWidgetEntity.h>
#include <tools/editor/ListWidgetComponents.h>

#include <age/entity/EntityManager.h>

using namespace age;
using namespace age::entity;

struct MainWindow::Impl
{
};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), pimpl()
{
	this->setWindowTitle("AgeEditor");
	this->setGeometry(80, 80, 1920, 1080);

	this->setCentralWidget(new QWidget());

	this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, new DockWidgetEntity());

	auto manager = Application::Instance()->getEngine().getChild<EntityManager>();
	auto entities = manager->getEntities();
	auto dlgComponents = new DialogComponents(entities[0], this);
	dlgComponents->show();
}

MainWindow::~MainWindow()
{
}

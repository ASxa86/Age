#include <tools/editor/MainWindow.h>

#include <age/core/Engine.h>
#include <age/core/PimplImpl.h>
#include <age/entity/EntityManager.h>
#include <tools/editor/Application.h>
#include <tools/editor/DockWidgetEntity.h>

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
}

MainWindow::~MainWindow()
{
}

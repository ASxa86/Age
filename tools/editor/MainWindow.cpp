#include <MainWindow.h>

#include <Application.h>
#include <DockWidgetComponent.h>
#include <DockWidgetEntity.h>
#include <azule/core/Engine.h>
#include <azule/utilities/PimplImpl.h>

using namespace azule;
using namespace azule;

struct MainWindow::Impl
{
};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), pimpl()
{
	this->setWindowTitle("AgeEditor");
	this->setGeometry(80, 80, 1920, 1080);

	this->setCentralWidget(new QWidget());

	this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, new DockWidgetEntity());
	this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, new DockWidgetComponent());
}

MainWindow::~MainWindow()
{
}

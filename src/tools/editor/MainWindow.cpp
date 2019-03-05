#include <tools/editor/MainWindow.h>

#include <age/core/PimplImpl.h>
#include <tools/editor/ListWidgetComponents.h>

using namespace age;

struct MainWindow::Impl
{
};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), pimpl()
{
	this->setWindowTitle("AgeEditor");
	this->setGeometry(80, 80, 1280, 720);

	this->setCentralWidget(new ListWidgetComponents());
}

MainWindow::~MainWindow()
{
}

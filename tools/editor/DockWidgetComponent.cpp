#include <Application.h>
#include <DockWidgetComponent.h>
#include <age/core/qt/DelegateWidgetProperty.h>
#include <age/core/qt/TableModelProperties.h>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

using namespace age;
using namespace age::core::qt;

DockWidgetComponent::DockWidgetComponent(QWidget* parent) : QDockWidget(parent)
{
	auto view = new QTableView();
	view->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	view->setItemDelegateForColumn(static_cast<int>(TableModelProperties::Column::Value), new DelegateWidgetProperty(view));
	this->setWidget(view);

	// Connect to application that signals when a component has been selected.
	// Delete model and apply new model with new component.
	this->connect(Application::Instance(), &Application::componentSelected, this, [view](age::entity::Component* x) {
		view->model()->deleteLater();
		view->selectionModel()->deleteLater();
		view->setModel(new TableModelProperties(x));
	});
}

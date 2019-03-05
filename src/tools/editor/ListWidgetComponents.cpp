#include <tools/editor/ListWidgetComponents.h>

#include <age/core/PimplImpl.h>
#include <tools/editor/ComponentFactory.h>

using namespace age;

struct ListWidgetComponents::Impl
{
};

ListWidgetComponents::ListWidgetComponents(QWidget* parent) : QListWidget(parent), pimpl()
{
	const auto components = ComponentFactory::Instance().getComponentList();

	for(const auto& component : components)
	{
		this->addItem(QString::fromStdString(component));
	}
}

ListWidgetComponents::~ListWidgetComponents()
{
}

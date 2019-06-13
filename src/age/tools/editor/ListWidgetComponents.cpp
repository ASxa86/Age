#include <age/entity/ComponentFactory.h>
#include <age/tools/editor/ListWidgetComponents.h>

using namespace age;
using namespace age::entity;

ListWidgetComponents::ListWidgetComponents(QWidget* parent) : QListWidget(parent)
{
	for(const auto& [name, creator] : ComponentFactory::Instance().FactoryMap)
	{
		this->addItem(QString::fromStdString(name));
	}
}

ListWidgetComponents::~ListWidgetComponents()
{
}

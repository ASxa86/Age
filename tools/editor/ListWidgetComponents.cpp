#include <ListWidgetComponents.h>
#include <azule/core/Reflection.h>
#include <azule/entity/Component.h>

using namespace azule;

ListWidgetComponents::ListWidgetComponents(QWidget* parent) : QListWidget(parent)
{
	const auto types = azule::core::Reflection::Instance().getTypes(typeid(azule::entity::Component));

	for(auto type : types)
	{
		this->addItem(QString::fromStdString(type->Name));
	}
}

ListWidgetComponents::~ListWidgetComponents()
{
}

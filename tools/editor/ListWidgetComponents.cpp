#include <ListWidgetComponents.h>
#include <age/core/Reflection.h>
#include <age/entity/Component.h>

using namespace age;

ListWidgetComponents::ListWidgetComponents(QWidget* parent) : QListWidget(parent)
{
	const auto types = age::core::Reflection::Instance().getTypes(typeid(age::entity::Component));

	for(auto type : types)
	{
		this->addItem(QString::fromStdString(type->Name));
	}
}

ListWidgetComponents::~ListWidgetComponents()
{
}

#include <age/core/Factory.h>
#include <age/entity/Component.h>
#include <editor/ListWidgetComponents.h>

using namespace age;

ListWidgetComponents::ListWidgetComponents(QWidget* parent) : QListWidget(parent)
{
	const auto types = age::core::Factory::Instance().getTypesFromBase(typeid(age::entity::Component));

	for(auto type : types)
	{
		this->addItem(QString::fromStdString(type.NameClean));
	}
}

ListWidgetComponents::~ListWidgetComponents()
{
}

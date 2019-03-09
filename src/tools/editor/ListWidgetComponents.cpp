#include <tools/editor/ListWidgetComponents.h>

#include <tools/editor/ComponentFactory.h>

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <rttr/registration.h>

#ifdef WIN32
#pragma warning(pop)
#endif

using namespace age;

ListWidgetComponents::ListWidgetComponents(QWidget* parent) : QListWidget(parent)
{
	const auto types = rttr::type::get_types();

	for(const auto& type : types)
	{
		const auto name = type.get_name();
		if(name.find("Component") != std::string::npos && name.find("*") == std::string::npos)
		{
			this->addItem(QString::fromStdString(name));
		}
	}
}

ListWidgetComponents::~ListWidgetComponents()
{
}

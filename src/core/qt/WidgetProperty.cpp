#include <azule/core/qt/WidgetProperty.h>

using namespace azule::core::qt;

WidgetProperty::WidgetProperty(QWidget* parent) : QWidget(parent)
{
}

WidgetProperty::~WidgetProperty()
{
}

void WidgetProperty::setValue(const std::string&)
{
}

std::string WidgetProperty::getValue() const
{
	return {};
}

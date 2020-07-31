#include  <azule/qt/WidgetProperty.h>

using namespace azule::qt;

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

#include  <azule/qt/export.h>
#include  <azule/qt/WidgetPropertyBool.h>
#include  <azule/qt/WidgetPropertyFactory.h>

using namespace azule::qt;

AZULE_QT_EXPORT_C void FactoryRegisterQt()
{
	WidgetPropertyFactory::RegisterType<WidgetPropertyBool, bool>();
}

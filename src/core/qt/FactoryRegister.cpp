#include <azule/core/qt/export.h>
#include <azule/core/qt/WidgetPropertyBool.h>
#include <azule/core/qt/WidgetPropertyFactory.h>

using namespace azule::core::qt;

AZULE_CORE_QT_EXPORT_C void FactoryRegisterQt()
{
	WidgetPropertyFactory::RegisterType<WidgetPropertyBool, bool>();
}

#include <age/core/qt/export.h>
#include <age/core/qt/WidgetPropertyBool.h>
#include <age/core/qt/WidgetPropertyFactory.h>

using namespace age::core::qt;

AGE_CORE_QT_EXPORT_C void FactoryRegisterQt()
{
	WidgetPropertyFactory::RegisterType<WidgetPropertyBool, bool>();
}

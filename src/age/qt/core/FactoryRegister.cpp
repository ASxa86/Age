#include <age/qt/core/Export.h>
#include <age/qt/core/WidgetPropertyBool.h>
#include <age/qt/core/WidgetPropertyFactory.h>

using namespace age::core::qt;

AGE_CORE_QT_EXPORT_C void FactoryRegisterQt()
{
	WidgetPropertyFactory::RegisterType<WidgetPropertyBool, bool>();
}

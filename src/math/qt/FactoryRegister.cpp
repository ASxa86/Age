#include <azule/core/qt/WidgetPropertyFactory.h>
#include <azule/math/qt/export.h>

#include <azule/math/Vector.h>
#include <azule/math/qt/WidgetVector.h>

using namespace age::core::qt;

AZULE_MATH_QT_EXPORT_C void FactoryRegisterQt()
{
	WidgetPropertyFactory::RegisterType<age::math::qt::WidgetVector, age::math::Vector>();
}

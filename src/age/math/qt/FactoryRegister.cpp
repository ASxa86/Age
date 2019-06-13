#include <age/core/qt/WidgetPropertyFactory.h>
#include <age/math/qt/Export.h>

#include <age/math/Vector.h>
#include <age/math/qt/WidgetVector.h>

using namespace age::core::qt;

AGE_MATH_QT_EXPORT_C void FactoryRegisterQt()
{
	WidgetPropertyFactory::RegisterType<age::math::qt::WidgetVector, age::math::Vector>();
}

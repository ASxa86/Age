#include <age/qt/core/WidgetPropertyFactory.h>
#include <age/qt/math/Export.h>

#include <age/math/Vector.h>
#include <age/qt/math/WidgetVector.h>

using namespace age::core::qt;

AGE_MATH_QT_EXPORT_C void FactoryRegisterQt()
{
	WidgetPropertyFactory::RegisterType<age::math::qt::WidgetVector, age::math::Vector>();
}

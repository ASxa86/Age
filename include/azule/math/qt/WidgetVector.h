#pragma once

#include <azule/utilities/Pimpl.h>
#include <azule/core/qt/WidgetProperty.h>
#include <azule/math/qt/export.h>
#include <QtWidgets/QWidget>

namespace azule
{
	namespace math
	{
		namespace qt
		{
			///
			///	\class WidgetVector
			///
			///	\brief A property widget for editing an azule::math::Vector property.
			///
			///	\date March 15, 2019
			///
			///	\author Aaron Shelley
			///
			class AZULE_MATH_QT_EXPORT WidgetVector : public azule::core::qt::WidgetProperty
			{
				Q_OBJECT

			public:
				WidgetVector(QWidget* parent = nullptr);
				virtual ~WidgetVector();

				void setValue(const std::string& x) override;
				std::string getValue() const override;

			private:
				struct Impl;
				Pimpl<Impl> pimpl;
			};
		}
	}
}

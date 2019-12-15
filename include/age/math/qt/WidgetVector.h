#pragma once

#include <age/core/Pimpl.h>
#include <age/core/qt/WidgetProperty.h>
#include <age/math/qt/export.h>
#include <QtWidgets/QWidget>

namespace age
{
	namespace math
	{
		namespace qt
		{
			///
			///	\class WidgetVector
			///
			///	\brief A property widget for editing an age::math::Vector property.
			///
			///	\date March 15, 2019
			///
			///	\author Aaron Shelley
			///
			class AGE_MATH_QT_EXPORT WidgetVector : public age::core::qt::WidgetProperty
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

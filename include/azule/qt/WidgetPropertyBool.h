#pragma once

#include <azule/utilities/Pimpl.h>
#include  <azule/qt/WidgetProperty.h>

namespace azule
{
	namespace core
	{
		namespace qt
		{
			class AZULE_QT_EXPORT WidgetPropertyBool : public WidgetProperty
			{
			public:
				WidgetPropertyBool(QWidget* parent = nullptr);

				void setValue(const std::string& x) override;
				std::string getValue() const override;

			private:
				struct Impl;
				Pimpl<Impl> pimpl;
			};
		}
	}
}

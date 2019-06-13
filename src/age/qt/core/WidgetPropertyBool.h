#pragma once

#include <age/core/Pimpl.h>
#include <age/qt/core/WidgetProperty.h>

namespace age
{
	namespace core
	{
		namespace qt
		{
			class AGE_CORE_QT_EXPORT WidgetPropertyBool : public WidgetProperty
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

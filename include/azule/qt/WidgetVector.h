#pragma once

#include <azule/qt/WidgetProperty.h>
#include <azule/qt/export.hxx>
#include <azule/utilities/Pimpl.h>
#include <QtWidgets/QWidget>

namespace azule
{
	namespace qt
	{
		///
		///	\class WidgetVector
		///
		///	\brief A property widget for editing an glm::vec2 property.
		///
		///	\date March 15, 2019
		///
		///	\author Aaron Shelley
		///
		class AZULE_QT_EXPORT WidgetVector : public azule::qt::WidgetProperty
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

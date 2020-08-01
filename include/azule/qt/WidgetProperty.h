#pragma once

#include <azule/qt/export.hxx>
#include <QtWidgets/QWidget>
#include <string>

namespace azule
{
	namespace qt
	{
		///
		///	\class WidgetProperty
		///
		///	\brief Abstract base class used to manage getting/setting the property system value to a derived widget.
		///
		///	This class makes it possible to generically handle property editors without knowing the type of the property at runtime.
		///	This also makes it possible to not have the property system as a dependency of the core engine and its data.
		///	Derived widgets of this class will generally be constructed from the WidgetPropertyFactory with an unknown type at run time.
		///
		///	\author Aaron Shelley
		///
		///	\date March 15, 2019
		///
		class AZULE_QT_EXPORT WidgetProperty : public QWidget
		{
			Q_OBJECT

		public:
			WidgetProperty(QWidget* parent = nullptr);
			virtual ~WidgetProperty() = 0;

			///
			///	Override to handle applying the data contained within the given argument to a derived property widget.
			///
			virtual void setValue(const std::string& x) = 0;

			///
			///	Override to handle returning the data within a property widget as a generic property argument.
			///
			virtual std::string getValue() const = 0;

		signals:
			void editingFinished();
		};
	}
}

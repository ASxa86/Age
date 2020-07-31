#pragma once

#include <azule/utilities/MagicEnum.h>
#include <QtWidgets/QComboBox>

namespace azule
{
	namespace qt
	{
		template <typename T>
		class ComboBoxEnum : public QComboBox
		{
		public:
			ComboBoxEnum(QWidget* parent = nullptr) : QComboBox(parent)
			{
				const auto entries = magic_enum::enum_entries<T>();

				for(const auto& [value, name] : entries)
				{
					this->addItem(QString::fromStdString(std::string(name)), static_cast<int>(value));
				}
			}

			void setCurrentEnum(T x)
			{
				this->setCurrentIndex(this->findData(static_cast<int>(x)));
			}

			T getCurrentEnum() const
			{
				return static_cast<T>(this->currentData().toInt());
			}
		};
	}
}

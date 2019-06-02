#pragma once

#include <age/qt/core/Export.h>
#include <QtCore/QAbstractTableModel>

namespace age
{
	namespace core
	{
		class Properties;

		namespace qt
		{
			class AGE_CORE_QT_EXPORT TableModelProperties : public QAbstractTableModel
			{
				Q_OBJECT

			public:
				enum class Column : int
				{
					Name,
					Value
				};

				TableModelProperties(age::core::Properties* x, QObject* parent = nullptr);

				int rowCount(const QModelIndex& parent = QModelIndex()) const override;
				int columnCount(const QModelIndex& parent = QModelIndex()) const override;
				QVariant headerData(int section, Qt::Orientation orientation, int role = 0) const override;
				bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
				QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
				Qt::ItemFlags flags(const QModelIndex& index) const override;

			private:
				age::core::Properties* properties{};
			};
		}
	}
}

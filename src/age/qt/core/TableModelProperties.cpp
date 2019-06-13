#include <age/core/MagicEnum.h>
#include <age/core/Properties.h>
#include <age/core/String.h>
#include <age/qt/core/TableModelProperties.h>

using namespace age::core;
using namespace age::core::qt;

Q_DECLARE_METATYPE(age::core::Property*);

TableModelProperties::TableModelProperties(age::core::Properties* x, QObject* parent) : QAbstractTableModel(parent), properties{x}
{
	qRegisterMetaType<age::core::Property*>();
}

int TableModelProperties::rowCount(const QModelIndex&) const
{
	return static_cast<int>(this->properties->getProperties().size());
}

int TableModelProperties::columnCount(const QModelIndex&) const
{
	return static_cast<int>(magic_enum::enum_count<Column>());
}

QVariant TableModelProperties::headerData(int section, Qt::Orientation orientation, int role) const
{
	QVariant data;

	if(role == Qt::DisplayRole)
	{
		switch(orientation)
		{
			case Qt::Orientation::Horizontal:
				data = QString::fromStdString(age::core::ToString(static_cast<Column>(section)));
				break;

			case Qt::Orientation::Vertical:
				data = section + 1;
				break;

			default:
				break;
		}
	}

	return data;
}

bool TableModelProperties::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if(index.isValid() == true)
	{
		if(role == Qt::EditRole)
		{
			const auto& props = this->properties->getProperties();
			const auto& prop = props[index.row()];

			switch(static_cast<Column>(index.column()))
			{
				case Column::Value:
					prop->setValue(value.toString().toStdString());
					break;

				case Column::Name:
					// Read Only //
				default:
					break;
			}

			this->dataChanged(index, index);
			return true;
		}
	}

	return false;
}

QVariant TableModelProperties::data(const QModelIndex& index, int role) const
{
	QVariant data;

	if(index.isValid() == true)
	{
		const auto& props = this->properties->getProperties();
		const auto& prop = props[index.row()];

		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			switch(static_cast<Column>(index.column()))
			{
				case Column::Name:
					data = QString::fromStdString(prop->getName());
					break;

				case Column::Value:
					data = QString::fromStdString(prop->getValue());
					break;

				default:
					break;
			}
		}
		else if(role == Qt::UserRole)
		{
			data = QVariant::fromValue(prop.get());
		}
	}

	return data;
}

Qt::ItemFlags TableModelProperties::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags = Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable;

	switch(static_cast<Column>(index.column()))
	{
		case Column::Name:
			// Read Only //
			break;

		case Column::Value:
			flags |= Qt::ItemFlag::ItemIsEditable;
			break;

		default:
			break;
	}

	return flags;
}

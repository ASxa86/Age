#include  <azule/qt/TableModelProperties.h>

#include <azule/core/Object.h>
#include <azule/utilities/MagicEnum.h>
#include <azule/core/Reflection.h>
#include <azule/utilities/String.h>

using namespace azule::core;
using namespace azule::core::qt;
using namespace azule::utilities;

Q_DECLARE_METATYPE(azule::core::ReflProp*);

TableModelProperties::TableModelProperties(azule::core::Object* x, QObject* parent) : QAbstractTableModel(parent), object{x}
{
	qRegisterMetaType<azule::core::ReflProp*>();
}

int TableModelProperties::rowCount(const QModelIndex&) const
{
	auto type = Reflection::Instance().get(*this->object);
	return static_cast<int>(type->getProperties().size());
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
				data = QString::fromStdString(azule::utilities::ToString(static_cast<Column>(section)));
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
			const auto type = Reflection::Instance().get(*this->object);
			const auto props = type->getProperties();
			const auto& prop = props[index.row()];

			switch(static_cast<Column>(index.column()))
			{
				case Column::Value:
					prop->setValue(*this->object, value.toString().toStdString());
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
		const auto type = Reflection::Instance().get(*this->object);
		const auto props = type->getProperties();
		const auto& prop = props[index.row()];

		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			switch(static_cast<Column>(index.column()))
			{
				case Column::Name:
					data = QString::fromStdString(prop->Name);
					break;

				case Column::Value:
					data = QString::fromStdString(prop->getValue(*this->object));
					break;

				default:
					break;
			}
		}
		else if(role == Qt::UserRole)
		{
			data = QVariant::fromValue(prop);
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

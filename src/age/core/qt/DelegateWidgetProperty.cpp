#include <age/core/Properties.h>
#include <age/core/qt/DelegateWidgetProperty.h>
#include <age/core/qt/WidgetPropertyFactory.h>
#include <QtWidgets/QLayout>

using namespace age::core::qt;

Q_DECLARE_METATYPE(age::core::Property*);

DelegateWidgetProperty::DelegateWidgetProperty(QObject* parent) : QStyledItemDelegate(parent)
{
	qRegisterMetaType<age::core::Property*>();
}

QString DelegateWidgetProperty::displayText(const QVariant& value, const QLocale&) const
{
	return value.toString();
}

QWidget* DelegateWidgetProperty::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
	const auto property = index.data(Qt::UserRole).value<age::core::Property*>();
	const auto editor = WidgetPropertyFactory::Instance().create(property->getTypeInfo(), parent);

	if(editor != nullptr)
	{
		// Set the layout of the widget to a fixed size to prevent the table from sizing the widget into the cell
		// if more space is required for editing.
		const auto layout = editor->layout();

		if(layout != nullptr)
		{
			layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
		}

		this->connect(editor, &WidgetProperty::editingFinished, this, &DelegateWidgetProperty::commitAndCloseEditor);
	}

	return editor;
}

void DelegateWidgetProperty::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	auto wProperty = static_cast<WidgetProperty*>(editor);
	wProperty->setValue(index.data(Qt::EditRole).toString().toStdString());
}

void DelegateWidgetProperty::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	auto wProperty = static_cast<WidgetProperty*>(editor);
	model->setData(index, QString::fromStdString(wProperty->getValue()));
}

void DelegateWidgetProperty::commitAndCloseEditor()
{
	auto editor = static_cast<WidgetProperty*>(this->sender());
	this->commitData(editor);
	this->closeEditor(editor);
}
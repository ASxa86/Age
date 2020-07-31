#pragma once

#include  <azule/qt/export.h>
#include <QtWidgets/QStyledItemDelegate>

namespace azule
{
	namespace core
	{
		namespace qt
		{
			class AZULE_QT_EXPORT DelegateWidgetProperty : public QStyledItemDelegate
			{
				Q_OBJECT

			public:
				DelegateWidgetProperty(QObject* parent = nullptr);

				QString displayText(const QVariant& value, const QLocale& locale) const override;
				QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
				void setEditorData(QWidget* editor, const QModelIndex& index) const override;
				void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

			private:
				void commitAndCloseEditor();
			};
		}
	}
}

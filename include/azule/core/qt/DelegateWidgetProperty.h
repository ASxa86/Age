#pragma once

#include <azule/core/qt/export.h>
#include <QtWidgets/QStyledItemDelegate>

namespace age
{
	namespace core
	{
		namespace qt
		{
			class AZULE_CORE_QT_EXPORT DelegateWidgetProperty : public QStyledItemDelegate
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

#include <age/core/qt/WidgetPropertyBool.h>

#include <age/utilities/PimplImpl.h>
#include <age/utilities/String.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QComboBox>

using namespace age::core::qt;

struct WidgetPropertyBool::Impl
{
	QComboBox* cbBool{new QComboBox()};
};

WidgetPropertyBool::WidgetPropertyBool(QWidget* parent) : WidgetProperty(parent)
{
	const auto vLayout = new QVBoxLayout(this);
	vLayout->setMargin(0);
	vLayout->addWidget(this->pimpl->cbBool);

	this->pimpl->cbBool->addItem(QString::fromStdString(age::utilities::ToString(true)), QVariant::fromValue(true));
	this->pimpl->cbBool->addItem(QString::fromStdString(age::utilities::ToString(false)), QVariant::fromValue(false));
	this->connect(this->pimpl->cbBool, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &WidgetProperty::editingFinished);
}

void WidgetPropertyBool::setValue(const std::string& x)
{
	this->pimpl->cbBool->setCurrentText(QString::fromStdString(x));
}

std::string WidgetPropertyBool::getValue() const
{
	return this->pimpl->cbBool->currentText().toStdString();
}

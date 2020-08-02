#include <azule/qt/WidgetVector.h>

#include <azule/utilities/PimplImpl.h>
#include <azule/utilities/String.h>
#include <azule/math/Vector.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>

using namespace azule::qt;
using namespace azule::qt;

struct WidgetVector::Impl
{
	QDoubleSpinBox* sbxX{new QDoubleSpinBox()};
	QDoubleSpinBox* sbxY{new QDoubleSpinBox()};
};

WidgetVector::WidgetVector(QWidget* parent) : WidgetProperty(parent), pimpl()
{
	const auto vLayout = new QVBoxLayout(this);
	vLayout->setMargin(0);

	auto menu = new QMenu();
	vLayout->addWidget(menu);

	const auto hLayout = new QHBoxLayout(menu);

	hLayout->addWidget(new QLabel("X:"));
	hLayout->addWidget(this->pimpl->sbxX);
	hLayout->addWidget(new QLabel("Y:"));
	hLayout->addWidget(this->pimpl->sbxY);

	this->connect(this->pimpl->sbxX, &QSpinBox::editingFinished, this, &WidgetProperty::editingFinished);
	this->connect(this->pimpl->sbxY, &QSpinBox::editingFinished, this, &WidgetProperty::editingFinished);
}

WidgetVector::~WidgetVector()
{
}

void WidgetVector::setValue(const std::string& x)
{
	const auto vector = azule::StringTo<glm::vec2>(x);
	this->pimpl->sbxX->setValue(vector.x);
	this->pimpl->sbxY->setValue(vector.y);
}

std::string WidgetVector::getValue() const
{
	return azule::ToString(glm::vec2{this->pimpl->sbxX->value(), this->pimpl->sbxY->value()});
}

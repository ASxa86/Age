#include <age/qt/math/WidgetVector.h>

#include <age/core/PimplImpl.h>
#include <age/math/Vector.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>

using namespace age::core::qt;
using namespace age::math::qt;

struct WidgetVector::Impl
{
	QDoubleSpinBox* sbxX{new QDoubleSpinBox()};
	QDoubleSpinBox* sbxY{new QDoubleSpinBox()};
};

WidgetVector::WidgetVector(QWidget* parent) : QWidget(parent), WidgetProperty(), pimpl()
{
	const auto hLayout = new QHBoxLayout(this);
	hLayout->setMargin(0);

	hLayout->addWidget(new QLabel("X:"));
	hLayout->addWidget(this->pimpl->sbxX);
	hLayout->addWidget(new QLabel("Y:"));
	hLayout->addWidget(this->pimpl->sbxY);
}

WidgetVector::~WidgetVector()
{
}

void WidgetVector::setValue(const rttr::argument& x)
{
	const auto& vector = x.get_value<age::math::Vector>();
	this->pimpl->sbxX->setValue(vector.X);
	this->pimpl->sbxY->setValue(vector.Y);
}

rttr::argument WidgetVector::getValue() const
{
	return Vector{this->pimpl->sbxX->value(), this->pimpl->sbxY->value()};
}

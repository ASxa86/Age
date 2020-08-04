#include <DialogComponents.h>
#include <ListWidgetComponents.h>
#include <azule/entity/Component.h>
#include <azule/entity/Entity.h>
#include <azule/core/ObjectFactory.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>

using namespace azule;

DialogComponents::DialogComponents(azule::Entity* e, QWidget* parent) : QDialog(parent), entity{e}
{
	const auto vLayout = new QVBoxLayout(this);
	const auto lwComponents = new ListWidgetComponents();
	const auto btnCreate = new QPushButton("Create");
	const auto btnCancel = new QPushButton("Cancel");

	const auto addComponent = [this, lwComponents] {
		const auto items = lwComponents->selectedItems();

		if(items.empty() == false)
		{
			auto c = ObjectFactory::Instance().create<Component>(items[0]->text().toStdString());
			this->entity->addComponent(c);
		}

		this->close();
	};

	this->connect(lwComponents, &QListWidget::doubleClicked, this, addComponent);
	this->connect(btnCreate, &QPushButton::clicked, this, addComponent);
	this->connect(btnCancel, &QPushButton::clicked, this, &QDialog::close);

	const auto hLayout = new QHBoxLayout();
	hLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	hLayout->addWidget(btnCreate);
	hLayout->addWidget(btnCancel);

	vLayout->addWidget(lwComponents);
	vLayout->addLayout(hLayout);
}

DialogComponents::~DialogComponents()
{
}

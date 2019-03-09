#include <tools/editor/DialogComponents.h>

#include <age/entity/Entity.h>
#include <tools/editor/ListWidgetComponents.h>
#include <tools/editor/Properties.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>

using namespace age;
using namespace age::entity;

DialogComponents::DialogComponents(age::entity::Entity e, QWidget* parent) : QDialog(parent), entity{e}
{
	const auto vLayout = new QVBoxLayout(this);
	const auto lwComponents = new ListWidgetComponents();
	vLayout->addWidget(lwComponents);

	const auto btnCreate = new QPushButton("Create");
	const auto btnCancel = new QPushButton("Cancel");

	this->connect(btnCreate, &QPushButton::clicked, this, [this, lwComponents] {
		const auto items = lwComponents->selectedItems();

		if(items.empty() == false)
		{
			Property p(this->entity);
			p.addComponent(items[0]->text().toStdString());
		}

		this->close();
	});

	this->connect(btnCancel, &QPushButton::clicked, this, &QDialog::close);

	const auto hLayout = new QHBoxLayout();
	hLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	hLayout->addWidget(btnCreate);
	hLayout->addWidget(btnCancel);

	vLayout->addLayout(hLayout);
}

DialogComponents::~DialogComponents()
{
}

#include <azule/core/Engine.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/System.h>

using namespace azule;

System::System() : azule::Processor()
{
}

System::~System()
{
}

EntityDatabase* System::getEntityDatabase() const
{
	const auto parent = this->getParent<azule::Engine>(FindOption::Recursive);

	if(parent != nullptr)
	{
		return parent->getChild<EntityDatabase>();
	}

	return nullptr;
}

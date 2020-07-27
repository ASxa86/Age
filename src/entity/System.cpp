#include <azule/core/Engine.h>
#include <azule/entity/EntityDatabase.h>
#include <azule/entity/System.h>

using namespace azule::entity;

System::System() : azule::core::Processor()
{
}

System::~System()
{
}

EntityDatabase* System::getEntityDatabase() const
{
	const auto parent = this->getParent<azule::core::Engine>(FindOption::Recursive);

	if(parent != nullptr)
	{
		return parent->getChild<EntityDatabase>();
	}

	return nullptr;
}

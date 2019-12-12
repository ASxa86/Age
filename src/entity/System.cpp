#include <age/core/Engine.h>
#include <age/entity/EntityDatabase.h>
#include <age/entity/System.h>

using namespace age::entity;

System::System() : age::core::Processor()
{
}

System::~System()
{
}

EntityDatabase* System::getEntityDatabase() const
{
	const auto parent = this->getParent<age::core::Engine>(FindOption::Recursive);

	if(parent != nullptr)
	{
		return parent->getChild<EntityDatabase>();
	}

	return nullptr;
}

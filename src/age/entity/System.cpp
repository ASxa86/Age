#include <age/entity/System.h>
#include <age/entity/EntityProcessor.h>

using namespace age::entity;

System::System() : age::core::Object()
{
}

System::~System()
{
}

entityx::EntityManager* System::getEntities() const
{
	const auto parent = this->getParent<EntityProcessor>();

	if(parent != nullptr)
	{
		return parent->getEntities();
	}

	return nullptr;
}

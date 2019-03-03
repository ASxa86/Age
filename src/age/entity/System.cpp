#include <age/core/Engine.h>
#include <age/entity/EntityManager.h>
#include <age/entity/System.h>

using namespace age::entity;

System::System() : age::core::Processor()
{
}

System::~System()
{
}

EntityManager* System::getEntityManager() const
{
	const auto parent = this->getParent<age::core::Engine>(true);

	if(parent != nullptr)
	{
		return parent->getChild<EntityManager>();
	}

	return nullptr;
}

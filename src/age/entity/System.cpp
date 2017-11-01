#include <age/entity/System.h>
#include <age/entity/EntityManager.h>

using namespace age::entity;

System::System() : age::core::Object()
{
}

System::~System()
{
}

EntityManager* System::getEntityManager() const
{
	const auto parent = this->getParent();

	if(parent != nullptr)
	{
		return parent->getChild<EntityManager>().get();
	}

	return nullptr;
}

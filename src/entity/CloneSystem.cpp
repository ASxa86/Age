#include <age/entity/CloneSystem.h>

#include <age/core/Utilities.h>
#include <age/entity/Entity.h>
#include <age/entity/EntityDatabase.h>

using namespace age::entity;

CloneSystem::CloneSystem()
{
	this->addFixedFunction([this](auto x) { this->frame(x); });
}

void CloneSystem::frame(std::chrono::microseconds x)
{
	if(this->Limit > 0 && this->Count < this->Limit || this->Limit < 0)
	{
		auto manager = this->getEntityDatabase();

		auto entity = this->getChild<Entity>();

		if(entity != nullptr)
		{
			if(this->Rate.count() > 0)
			{
				this->elapsed += x;

				if(this->elapsed >= this->Rate)
				{
					++this->Count;
					this->elapsed -= this->Rate;

					auto clone = age::core::Clone(entity);
					std::unique_ptr<Entity> ce{dynamic_cast<Entity*>(clone.release())};
					manager->addEntity(std::move(ce));
				}
			}
		}
	}
}

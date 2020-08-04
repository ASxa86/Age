#include <azule/entity/CloneSystem.h>

#include <azule/core/Utilities.h>
#include <azule/entity/Entity.h>
#include <azule/entity/EntityDatabase.h>

using namespace azule;

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

					auto clone = azule::Clone(entity.get());
					auto ce = std::dynamic_pointer_cast<Entity>(clone);
					manager->addEntity(std::move(ce));
				}
			}
		}
	}
}

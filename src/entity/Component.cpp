#include <azule/entity/Component.h>

using namespace azule;

Component::Component()
{
	this->addProperty("Enabled", this->Enabled);
}

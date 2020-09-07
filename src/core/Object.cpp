#include <azule/core/Object.h>

using namespace azule;

Object::Object()
{
	this->addProperty("id", this->id);
}

Object::~Object()
{
}

void Object::setID(const std::string& x)
{
	this->id = x;
}

std::string Object::getID() const
{
	return this->id;
}

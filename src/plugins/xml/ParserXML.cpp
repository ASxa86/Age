#include <azule/core/Object.h>
#include <azule/core/Reflection.h>
#include <azule/core/Utilities.h>
#include <azule/plugins/xml/ParserXML.h>
#include <iostream>
#include <pugixml.hpp>

using namespace azule;
using namespace azule;
using namespace azule::xml;

namespace
{
	bool ParsePropertyTag(const pugi::xml_node& x, Object* obj)
	{
		if(x.empty() == false)
		{
			auto type = Reflection::Instance().get(*obj);
			auto prop = type->getProperty(x.attribute("name").as_string());

			if(prop != nullptr)
			{
				const auto value = azule::ResolvePath(x.attribute("value").as_string());
				prop->setValue(*obj, value);
				return true;
			}
			else
			{
				std::cerr << type->Name << " did not have property \"" << x.attribute("name").as_string() << "\"\n";
			}
		}

		return false;
	}

	std::unique_ptr<Object> ParseObjectTag(const pugi::xml_node& x)
	{
		std::unique_ptr<Object> obj;

		if(x.empty() == false)
		{
			const auto type = x.attribute("type").as_string();
			const auto id = x.attribute("id").as_string();
			obj = Reflection::Instance().create(type);

			if(obj != nullptr)
			{
				obj->setID(id);

				for(const auto& property : x.children("property"))
				{
					ParsePropertyTag(property, obj.get());
				}

				for(const auto& child : x.children("object"))
				{
					obj->addChild(ParseObjectTag(child));
				}
			}
			else
			{
				std::cerr << "[XML] Failed to construct " << type << "\n";
			}
		}

		return obj;
	}
}

ParserXML::ParserXML()
{
}

ParserXML::~ParserXML()
{
}

bool ParserXML::readFile(const std::filesystem::path& x, Object* obj)
{
	if(std::filesystem::exists(x) == true)
	{
		pugi::xml_document doc;
		if(doc.load_file(x.c_str()).status == pugi::xml_parse_status::status_ok)
		{
			auto root = doc.child("azule");

			if(root.empty() == false)
			{
				auto objects = root.children("object");

				for(const auto& object : objects)
				{
					obj->addChild(ParseObjectTag(object));
				}

				return true;
			}
		}
	}

	std::cerr << "Failed to load " << x << "\n";

	return false;
}

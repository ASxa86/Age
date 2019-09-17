#include <age/core/Factory.h>
#include <age/core/Object.h>
#include <age/core/Utilities.h>
#include <age/plugins/xml/ParserXML.h>
#include <iostream>
#include <pugixml.hpp>

using namespace age::core;
using namespace age::xml;

namespace
{
	bool ParsePropertyTag(const pugi::xml_node& x, Object* obj)
	{
		if(x.empty() == false)
		{
			auto property = obj->getProperty(x.attribute("name").as_string());

			if(property != nullptr)
			{
				const auto value = age::core::ResolvePath(x.attribute("value").as_string());
				property->setValue(value);
				return true;
			}
			else
			{
				std::cerr << "Object did not have property \"" << x.attribute("name").as_string() << "\"\n";
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
			obj = Factory::Instance().create(type);

			if(obj != nullptr)
			{
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
				std::cerr << "Factory failed to construct " << type << "\n";
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
			auto root = doc.child("age");

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

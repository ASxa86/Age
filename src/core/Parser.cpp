#include <azule/core/Parser.h>
#include <azule/core/ObjectFactory.h>
#include <azule/utilities/PimplImpl.h>

using namespace azule;

struct Parser::Impl
{
	std::string extension;
};

Parser::Parser()
{
}

Parser::~Parser()
{
}

bool Parser::readFile(const std::filesystem::path&, Object*)
{
	return false;
}

bool Parser::writeFile(const Object& obj, const std::filesystem::path& x)
{
	return false;
}

bool azule::ReadFile(const std::filesystem::path& x, Object* obj)
{
	const auto parser = ObjectFactory::Instance().create<Parser>(x.extension().string());

	if(parser != nullptr)
	{
		return parser->readFile(x, obj);
	}

	return false;
}

bool azule::WriteFile(const Object& obj, const std::filesystem::path& x)
{
	const auto parser = ObjectFactory::Instance().create<Parser>(x.extension().string());

	if (parser != nullptr)
	{
		return parser->writeFile(obj, x);
	}

	return false;
}


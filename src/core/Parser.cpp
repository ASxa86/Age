#include <age/core/Parser.h>

#include <age/core/Reflection.h>
#include <age/utilities/PimplImpl.h>

using namespace age::core;

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

bool age::core::ReadFile(const std::filesystem::path& x, Object* obj)
{
	const auto parser = Reflection::Instance().create<Parser>(x.extension().string());

	if(parser != nullptr)
	{
		return parser->readFile(x, obj);
	}

	return false;
}

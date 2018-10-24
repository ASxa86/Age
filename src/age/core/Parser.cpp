#include <age/core/Parser.h>

#include <age/core/Factory.h>
#include <age/core/PimplImpl.h>

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

bool Parser::readFile(const std::filesystem::path&, std::shared_ptr<Object>)
{
	return false;
}

bool age::core::ReadFile(const std::filesystem::path& x, std::shared_ptr<Object> obj)
{
	const auto parser = Factory::Instance().create<Parser>(x.extension().string());

	if(parser != nullptr)
	{
		return parser->readFile(x, obj);
	}

	return false;
}

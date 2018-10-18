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

std::shared_ptr<Object> Parser::readFile(const std::filesystem::path&)
{
	return nullptr;
}

std::shared_ptr<Object> age::core::ReadFile(const std::filesystem::path& x)
{
	const auto parser = Factory::Instance().create<Parser>(x.extension().string());

	if(parser != nullptr)
	{
		return parser->readFile(x);
	}

	return nullptr;
}

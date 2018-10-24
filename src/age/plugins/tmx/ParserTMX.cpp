#include <age/plugins/tmx/ParserTMX.h>
#include <iostream>
using namespace age::core;
using namespace age::tmx;

ParserTMX::ParserTMX()
{
}

ParserTMX::~ParserTMX()
{
}

bool ParserTMX::readFile(const std::filesystem::path&, std::shared_ptr<Object> obj)
{
	return false;
}

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

std::shared_ptr<Object> ParserTMX::readFile(const std::filesystem::path&)
{
	return nullptr;
}

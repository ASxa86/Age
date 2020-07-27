#include <age/core/Reflection.h>
#include <age/plugins/xml/ParserXML.h>
#include <age/utilities/StaticInvoke.h>

using namespace age::core;
using namespace age::xml;

STATIC_INVOKE
{
	Reflection::Instance().add<Parser>("Parser");
	Reflection::Instance().add<ParserXML>("ParserXML").addAlias("xml").addAlias(".xml").addBase<Parser>();
}

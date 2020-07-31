#include <azule/core/Reflection.h>
#include <azule/plugins/xml/ParserXML.h>
#include <azule/utilities/StaticInvoke.h>

using namespace azule;
using namespace azule::xml;

STATIC_INVOKE
{
	Reflection::Instance().add<Parser>("Parser");
	Reflection::Instance().add<ParserXML>("ParserXML").addAlias("xml").addAlias(".xml").addBase<Parser>();
}

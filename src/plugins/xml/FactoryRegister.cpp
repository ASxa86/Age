#include <azule/core/ObjectFactory.h>
#include <azule/plugins/xml/ParserXML.h>
#include <azule/utilities/StaticInvoke.h>

STATIC_INVOKE
{
	ObjectFactoryRegisterAlias(azule::xml::ParserXML, ".xml");
}

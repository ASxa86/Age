#include <age/core/Factory.h>
#include <age/plugins/xml/ParserXML.h>

AGE_XML_EXPORT_C void FactoryRegister()
{
	AgeFactoryRegister(age::xml::ParserXML).addAlias("xml").addAlias(".xml").addBaseType<age::core::Parser>();
}

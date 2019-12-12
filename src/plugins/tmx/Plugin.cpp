#include <age/core/Factory.h>
#include <age/plugins/tmx/ParserTMX.h>

AGE_PLUGINS_TMX_EXPORT_C void FactoryRegister()
{
	AgeFactoryRegister(age::tmx::ParserTMX).addAlias("tmx").addAlias(".tmx").addBaseType<age::core::Parser>();
}

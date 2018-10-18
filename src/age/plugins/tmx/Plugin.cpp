#include <age/core/Factory.h>
#include <age/plugins/tmx/ParserTMX.h>

AGE_TMX_EXPORT_C void FactoryRegister()
{
	age::core::Factory::RegisterType<age::tmx::ParserTMX>();
	age::core::Factory::RegisterType<age::tmx::ParserTMX>("tmx");
	age::core::Factory::RegisterType<age::tmx::ParserTMX>(".tmx");
}

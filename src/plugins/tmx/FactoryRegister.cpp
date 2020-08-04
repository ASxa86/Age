#include <azule/plugins/tmx/ParserTMX.h>
#include <azule/utilities/StaticInvoke.h>
#include <azule/core/ObjectFactory.h>

STATIC_INVOKE
{
	ObjectFactoryRegisterAlias(azule::tmx::ParserTMX, ".tmx");
}

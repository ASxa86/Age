#include <azule/core/Reflection.h>
#include <azule/plugins/tmx/ParserTMX.h>
#include <azule/utilities/StaticInvoke.h>

using namespace azule;
using namespace azule::tmx;

STATIC_INVOKE
{
	Reflection::Instance().add<ParserTMX>("ParserTMX").addAlias("tmx").addAlias(".tmx").addBase<Parser>();
}

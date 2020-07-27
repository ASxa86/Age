#include <age/core/Reflection.h>
#include <age/plugins/tmx/ParserTMX.h>
#include <age/utilities/StaticInvoke.h>

using namespace age::core;
using namespace age::tmx;

STATIC_INVOKE
{
	Reflection::Instance().add<ParserTMX>("ParserTMX").addAlias("tmx").addAlias(".tmx").addBase<Parser>();
}

#pragma once

#include <azule/core/Parser.h>
#include <azule/plugins/tmx/export.h>

namespace azule
{
	namespace tmx
	{
		class AZULE_PLUGINS_TMX_EXPORT ParserTMX : public azule::Parser
		{
		public:
			ParserTMX();
			~ParserTMX();

			bool readFile(const std::filesystem::path& x, Object* obj) override;
		};
	}
}

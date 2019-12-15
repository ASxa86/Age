#pragma once

#include <age/core/Parser.h>
#include <age/plugins/tmx/export.h>

namespace age
{
	namespace tmx
	{
		class AGE_PLUGINS_TMX_EXPORT ParserTMX : public age::core::Parser
		{
		public:
			ParserTMX();
			~ParserTMX();

			bool readFile(const std::filesystem::path& x, Object* obj) override;
		};
	}
}

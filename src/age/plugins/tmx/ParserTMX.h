#pragma once

#include <age/core/Parser.h>
#include <age/plugins/tmx/Export.h>

namespace age
{
	namespace tmx
	{
		class AGE_TMX_EXPORT ParserTMX : public age::core::Parser
		{
		public:
			ParserTMX();
			~ParserTMX();

			std::shared_ptr<Object> readFile(const std::filesystem::path& x) override;
		};
	}
}

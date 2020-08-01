#pragma once

#include <azule/core/Parser.h>

namespace azule
{
	namespace tmx
	{
		class ParserTMX : public azule::Parser
		{
		public:
			ParserTMX();
			~ParserTMX();

			bool readFile(const std::filesystem::path& x, Object* obj) override;
		};
	}
}

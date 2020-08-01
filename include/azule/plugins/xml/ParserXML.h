#pragma once

#include <azule/core/Parser.h>

namespace azule
{
	namespace xml
	{
		class ParserXML : public azule::Parser
		{
		public:
			ParserXML();
			~ParserXML();

			bool readFile(const std::filesystem::path& x, Object* obj) override;
			bool writeFile(const Object& obj, const std::filesystem::path& x) override;
		};
	}
}

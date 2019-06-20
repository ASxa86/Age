#pragma once

#include <age/core/Parser.h>
#include <age/plugins/xml/Export.h>

namespace age
{
	namespace xml
	{
		class AGE_XML_EXPORT ParserXML : public age::core::Parser
		{
		public:
			ParserXML();
			~ParserXML();

			bool readFile(const std::filesystem::path& x, Object* obj) override;
		};
	}
}

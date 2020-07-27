#pragma once

#include <age/core/Parser.h>
#include <age/plugins/xml/export.h>

namespace age
{
	namespace xml
	{
		class AGE_PLUGINS_XML_EXPORT ParserXML : public age::core::Parser
		{
		public:
			ParserXML();
			~ParserXML();

			bool readFile(const std::filesystem::path& x, Object* obj) override;
		};
	}
}

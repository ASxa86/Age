#pragma once

#include <azule/core/Parser.h>
#include <azule/plugins/xml/export.h>

namespace azule
{
	namespace xml
	{
		class AZULE_PLUGINS_XML_EXPORT ParserXML : public azule::Parser
		{
		public:
			ParserXML();
			~ParserXML();

			bool readFile(const std::filesystem::path& x, Object* obj) override;
		};
	}
}

#include <age/core/Configuration.h>
#include <age/core/Factory.h>
#include <age/core/Object.h>
#include <age/core/Utilities.h>

double age::core::PixelsToMeters(unsigned int x)
{
	return static_cast<double>(x) / static_cast<double>(age::core::Configuration::Instance().getPixelsPerMeter());
}

std::unique_ptr<age::core::Object> age::core::Clone(age::core::Object* x)
{
	auto clone = age::core::Factory::Instance().create(typeid(*x));

	if(clone != nullptr)
	{
		for(const auto& property : x->getProperties())
		{
			auto p = clone->getProperty(property->getName());
			p->setValue(property->getValue());
		}

		for(auto child : x->getChildren())
		{
			clone->addChild(age::core::Clone(child));
		}
	}

	return clone;
}

std::string age::core::ResolvePath(std::string x)
{
	if(x.empty() == false)
	{
		if(x[0] == '$')
		{
			const auto tokenPos = x.find_first_of("/\\");
			const auto pathAlias = x.substr(0, tokenPos);
			const auto leafPath = x.substr(tokenPos);
			return Configuration::Instance().getPath(pathAlias).string() + leafPath;
		}
	}

	return x;
}

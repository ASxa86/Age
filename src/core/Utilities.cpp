#include <azule/core/Configuration.h>
#include <azule/core/Object.h>
#include <azule/core/Reflection.h>
#include <azule/core/Utilities.h>

double azule::core::PixelsToMeters(unsigned int x)
{
	return static_cast<double>(x) / static_cast<double>(azule::core::Configuration::Instance().getPixelsPerMeter());
}

std::unique_ptr<azule::core::Object> azule::core::Clone(azule::core::Object* x)
{
	const auto type = azule::core::Reflection::Instance().get(*x);
	auto clone = type->create();

	if(clone != nullptr)
	{
		for(const auto& property : type->getProperties())
		{
			property->setValue(*clone, property->getValue(*x));
		}

		for(auto child : x->getChildren())
		{
			clone->addChild(azule::core::Clone(child));
		}
	}

	return clone;
}

std::string azule::core::ResolvePath(std::string x)
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

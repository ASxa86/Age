#include <age/core/Configuration.h>
#include <age/core/Object.h>
#include <age/core/Reflection.h>
#include <age/core/Utilities.h>

double age::core::PixelsToMeters(unsigned int x)
{
	return static_cast<double>(x) / static_cast<double>(age::core::Configuration::Instance().getPixelsPerMeter());
}

std::unique_ptr<age::core::Object> age::core::Clone(age::core::Object* x)
{
	const auto type = age::core::Reflection::Instance().get(*x);
	auto clone = type->create();

	if(clone != nullptr)
	{
		for(const auto& property : type->getProperties())
		{
			property->setValue(*clone, property->getValue(*x));
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

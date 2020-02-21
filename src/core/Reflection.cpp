#include <age/core/Configuration.h>
#include <age/core/Reflection.h>
#include <age/utilities/StaticInvoke.h>
#include <algorithm>
#include <iostream>

using namespace age::core;

STATIC_INVOKE
{
	Reflection::Instance().add<Object>("Object").addMethod("ID", &Object::setID, &Object::getID);
}

ReflProp::ReflProp(const std::string& n) : Name{n}
{
}

ReflProp::~ReflProp()
{
}

ReflType::ReflType() : baseTypeIt{std::end(Reflection::Instance().reflMap)}, index{typeid(ReflType)}
{
}

ReflType::ReflType(const std::string& n, const std::type_info& x)
	: Name{n}, baseTypeIt{std::end(Reflection::Instance().reflMap)}, index{typeid(ReflType)}
{
}

ReflType& ReflType::addAlias(const std::string& x)
{
	this->aliases.insert(x);
	return *this;
}

ReflProp* ReflType::getProperty(std::string_view x) const
{
	const auto properties = this->getProperties();
	const auto foundIt = std::find_if(std::begin(properties), std::end(properties), [x](ReflProp* p) { return p->Name == x; });

	if(foundIt != std::end(properties))
	{
		return *foundIt;
	}

	return nullptr;
}

std::vector<ReflProp*> ReflType::getProperties() const
{
	std::vector<ReflProp*> v;

	if(this->baseTypeIt != std::end(Reflection::Instance().reflMap))
	{
		auto props = this->baseTypeIt->second.getProperties();
		v.insert(std::end(v), std::begin(props), std::end(props));
	}

	v.reserve(this->properties.size() + v.size());

	std::transform(std::begin(this->properties), std::end(this->properties), std::back_inserter(v), [](const auto& x) { return x.get(); });

	return v;
}

bool ReflType::operator==(const ReflType& rhs) const
{
	auto equalsBaseType = false;

	if(this->baseTypeIt != std::end(Reflection::Instance().reflMap))
	{
		equalsBaseType = this->baseTypeIt->second == rhs;
	}

	return this->index == rhs.index || equalsBaseType;
}

std::unique_ptr<Object> ReflType::create() const
{
	if(this->Creator != nullptr)
	{
		return this->Creator->create();
	}

	return nullptr;
}

Reflection& Reflection::Instance()
{
	static Reflection singleton;

	if(singleton.initialized == false)
	{
		// Prevent re-entering this block of code to prevent calls to factoryRegister() from
		// causing a recursive loop.
		singleton.initialized = true;

		std::vector<std::filesystem::path> ageLibraries;

		const auto agecore = Configuration::Instance().getPathBin();
		if(std::filesystem::exists(agecore) == true)
		{
			for(const auto& it : std::filesystem::directory_iterator(agecore))
			{
				if(std::filesystem::is_regular_file(it) == true && it.path().extension() == ".dll")
				{
					const auto filepath = it.path();
					ageLibraries.push_back(it.path());
				}
			}
		}

		const auto plugins = Configuration::Instance().getPathPlugins();

		if(std::filesystem::exists(plugins) == true)
		{
			for(const auto& it : std::filesystem::directory_iterator(plugins))
			{
				if(std::filesystem::is_regular_file(it) == true && it.path().extension() == ".dll")
				{
					const auto filepath = it.path();
					ageLibraries.push_back(it.path());
				}
			}
		}

		for(const auto& filepath : ageLibraries)
		{
			const auto filename = filepath.filename().string();

			const std::string agePlugin = "age-";
			if(filename.compare(0, agePlugin.size(), agePlugin) == 0)
			{
				age::utilities::SharedLibrary library(filepath);

				if(library.loaded() == true)
				{
					const auto factoryRegister = library.symbol("FactoryRegister");

					if(factoryRegister != nullptr)
					{
						factoryRegister();
					}

					// Keep track of loaded libraries in order to keep them loaded in memory.
					singleton.libraries.push_back(library);
				}
				else
				{
					std::cerr << "Failed to load: " << filepath << "\n";
				}
			}
		}
	}

	return singleton;
}

void Reflection::clear()
{
	this->reflMap.clear();
}

std::unique_ptr<Object> Reflection::create(std::string_view x) const
{
	const auto type = this->get(x);

	if(type != nullptr)
	{
		return type->create();
	}

	return nullptr;
}

std::unique_ptr<Object> Reflection::create(const Object& x) const
{
	const auto type = this->get(typeid(x));

	if(type != nullptr)
	{
		return type->create();
	}

	return nullptr;
}

const ReflType* const Reflection::get(std::string_view x) const
{
	for(const auto& [index, type] : this->reflMap)
	{
		if(type.Name == x)
		{
			return &type;
		}
		else
		{
			const auto foundIt = std::find(std::begin(type.aliases), std::end(type.aliases), x);

			if(foundIt != std::end(type.aliases))
			{
				return &type;
			}
		}
	}

	return nullptr;
}

const ReflType* const Reflection::get(const std::type_info& x) const
{
	const auto foundIt = this->reflMap.find(x);

	if(foundIt != std::end(this->reflMap))
	{
		return &foundIt->second;
	}

	return nullptr;
}

std::vector<const ReflType*> const Reflection::getTypes(const std::type_info& x) const
{
	std::vector<const ReflType*> types;

	for(const auto& [index, type] : this->reflMap)
	{
		if(index == x)
		{
			types.push_back(&type);
		}
		else if(type.baseTypeIt != std::end(this->reflMap) && (*type.baseTypeIt).first == x)
		{
			types.push_back(&type);
		}
	}

	return types;
}
